//
// Created by Jürgen Schwietering on 11/17/15.
//

#ifndef TDOA_NET_TDOAESTIMATE_H
#define TDOA_NET_TDOAESTIMATE_H

#include <math.h>
#include <assert.h>
#include <vector>

template<typename _T>
struct Point
{
public:
    Point() :x(0),y(0),z(0) {
    }

    Point( _T x,  _T y,  _T z): x(x), y(y), z(z) {
    }
    _T x, y, z;
};

template<typename _T>
class TDOAEstimatePosition
{
public:

    TDOAEstimatePosition (const std::vector<Point<_T> > &sensors)
        : sensors(sensors)
    {
    }

    /* go into different directions (-3,+3 voxels) and determine better fit
     *                      .
     *                      .
     *                      .
     * |--e--|--e--|--e--|--v--|--e--|--e--|--e--|
     *                      .
     *                      .
     *                      .
     * */

    void computeGoodMatch(
        const std::vector<_T> &desiredArrivalTimes
        , _T maxError
        , Point<_T>  &origin)
    {

        _T epsilon = 0.8;
        Point<_T>  center(0.5, 0.5, 0.5);
        Point<_T>  bestMatch(0, 0, 0);
        while (epsilon > maxError) {
            DetermineBetter(center, desiredArrivalTimes, epsilon, bestMatch);
            center = bestMatch;
            epsilon *= 0.9;
        }
        origin = center;
    }

    std::vector<_T>  getTimeDelayForPoint( const Point<_T>  &pt) const
    {
        std::vector<_T> tdoa;
        for (std::size_t p = 0; p < sensors.size(); p++) {
            _T dt = getDistance(pt, sensors[p]);
            tdoa.push_back(dt);
        }
        return tdoa;
    }

private:
    _T inline getDistance(const Point<_T>  &p1, const Point<_T>  &p2) const
    {
        return sqrt(  ((p2.x - p1.x) * (p2.x - p1.x))
                      + ((p2.y - p1.y) * (p2.y - p1.y))
                      + ((p2.z - p1.z) * (p2.z - p1.z)));
    }

    _T compareTDOA(const std::vector<_T> &t1,const std::vector<_T> &t2)
    {
        double sum=0.0;
        assert(t1.size() == t2.size());
        for (std::size_t i = 0; i < t1.size(); ++i)
        {
            if (isnan(t1[i]))
                continue;
            if (isnan(t2[i]))
                continue;
            sum+=fabs(t1[i]-t2[i]);
        }
        return sum;
    }

    void DetermineBetter(
        const Point<_T> &center
        , const std::vector<_T> &desiredArrivalTimes
        , _T epsilon
        , Point<_T> &bestMatchingPoint)
    {
        double bestError = 1E36;
        Point<_T> bestPt(0,0,0);
        for (int z=-3; z<=3;++z) {
            for (int y = -3; y <= 3; ++y) {
                for (int x = -3; x <= 3; ++x) {

                    Point<_T> pt(center.x + static_cast<_T>(x)*epsilon
                        , center.y + static_cast<_T>(y)*epsilon
                        , center.z+static_cast<_T>(z)*epsilon);
                    std::vector<_T> tdoa = getTimeDelayForPoint(pt);
                    _T error = compareTDOA(desiredArrivalTimes, tdoa);
                    if (error < bestError)
                    {
                        bestPt = pt;
                        bestError = error;
                    }
                }
            }
        }
        bestMatchingPoint = bestPt;
    }

    const std::vector<Point<_T> > &sensors;
};



#endif //TDOA_NET_TDOAESTIMATE_H