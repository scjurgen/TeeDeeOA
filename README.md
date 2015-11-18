
#TDOA in space

POC for determing a source/emitter position by using the traveltime of a signal.

The calculation is normalized, that means, 2 sensors at a distance of one unit are supposed to have a traveltime of 1 unit -> distance*c equals traveltime*c (c being a constant for the unit of choice).

If you use microphones it means that 2 sensors at a distance of 340m will have a traveltime of 340 (and not 1sec).

##CMakeLists.txt

I use clion as platform, making debugging and refactoring a childplay. N.B. that the CMakeLists.txt sets the buildpath to set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/").

##Unittest

For unittesting I am using googletest (installed as a submodule).
Select the TDOAEstimatePosition_Unittest to run.


##Todo

In order of importance:

Unittest for non normalized to 1.0 but realworld distances (meters or feet).

Add more unittests for lost mic and errors in timing.

Determine impossible run times of a signal (i.e. 2 sensors of distance 1.0 can not have a traveltime of > 1.1)

Add real mic measurements and autocorrelation.

Compensate for mediumchanges (sound travel time in cold or hot air, wind sheer, humidity) [https://en.wikipedia.org/wiki/Speed_of_sound#Details].

Visualize sensor positions in a cube with projections.

Optimize search algorithm.

