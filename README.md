
#TDOA in space

POC for determing a sourceposition by traveltime of a signal

the calculation is normalized, that means, 2 sensors at a distance of one unit suppose to have a traveltime of 1 unit.
If you use air it means. 2 sensors at a distance of 330m will have a traveltime of 330 (and not 1).


##Unittest

googletest should be installed as a submodule
Select the TDOAEstimatePosition_Unittest to run



#Todo

Determine impossible run times of a signal (i.e. 2 sensors of distance 1.0 can not have a traveltime of > 1.1)

Compensate for mediumchanges (sound travel time in cold or hot air, wind sheer, humidity) [https://en.wikipedia.org/wiki/Speed_of_sound#Details]

Visualize sensor positions in a cube with projections.
