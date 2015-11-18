// TDOA-net.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <limits>
#include <stdio.h>
#include "TDOAEstimatePosition.h"


template<typename _T>
class TestTDOA
{
public:
    const std::vector< Point<_T> > &testcases;
    const std::vector< Point<_T> > microphoneCoordinates;

    TestTDOA (const std::vector<Point<_T> > &testcases, const std::vector<Point<_T> > microphoneCoordinates)
        : testcases(testcases), microphoneCoordinates(microphoneCoordinates)
    {
    }


    /**
     * round robin test:
     * calculate time delay of arrival from a suppose position in space to our test microphones,
     * Use this tdoa to calculate the point in space and check back
     */
    void runTest ()
    {
        for (size_t i = 0; i < testcases.size(); ++i)
        {
            std::vector<_T> soundWaveArrivalTimes;

            TDOAEstimatePosition<_T> tdoaEstimatePosition(microphoneCoordinates);
            Point<_T> desiredCenter = testcases[i];
            Point<_T> originFound;
            _T error;
            soundWaveArrivalTimes = tdoaEstimatePosition.getTimeDelayForPoint(desiredCenter);

            // simulate errors
            // values that contain NAN will be not considered in the estimation of a possible transmission position
            soundWaveArrivalTimes[rand() % soundWaveArrivalTimes.size()] = std::numeric_limits<_T>::quiet_NaN();
            //soundWaveArrivalTimes[rand() % soundWaveArrivalTimes.size()] += 0.00001;

            tdoaEstimatePosition.computeGoodMatch(soundWaveArrivalTimes, 1E-14, originFound);
            error = fabs(originFound.x - desiredCenter.x)
                    + fabs(originFound.y - desiredCenter.y)
                    + fabs(originFound.z - desiredCenter.z);
            // show error as log10 value
            printf("%s %.1f %17.13g %17.13g %17.13g\n", (error > 1.0E-12) ? "***" : "   ", log(error) / log(10),
                   originFound.x, originFound.y, originFound.z);
        }
    }
};


/*
* the sensor grid can also detect emissions outside of the bounding box of the sensors(microphones)
*/
template<typename _T>

std::vector<Point<_T> > createTestCases (size_t cnt)
{
    std::vector<Point<_T> > testcases;
    testcases.clear();
    const _T range = 4.0; // create test soundemitters in cube -range/2 to range*2
    for (size_t i = 0; i < cnt; i++)
    {
        Point<_T> tp(range / 2.0 - range * (_T) rand() / (RAND_MAX + 1.0),
                     range / 2.0 - range * (_T) rand() / (RAND_MAX + 1.0),
                     range / 2.0 - range * (_T) rand() / (RAND_MAX + 1.0));
        testcases.push_back(tp);
    }
    return testcases;
}


int main (int argc, char *argv[])
{
    std::vector<Point<double> > testCases = createTestCases<double>(100);
    std::vector<Point<double> > microphoneCoordinates = {
        {0.1, 0.2, 0.2 }, // left front
        {0.8, 0.2, 0.2 }, // right front
        {0.9, 0.8, 0.24}, // right back
        {0.7, 0.4, 0.8 }, // mic high up
        {0.2, 0.8,-0.1 }, // left back + mic lower than plane
        {0.3, 0.5, 0.4 },  // mic nedium up
        {0.5, 0.5, 0.1 }, // center down
    };
    TestTDOA<double> testTDOA(testCases, microphoneCoordinates);
    testTDOA.runTest();
    return 0;
}

