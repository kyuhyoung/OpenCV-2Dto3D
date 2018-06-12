# OpenCV-2Dto3D

Based on:

* https://stackoverflow.com/questions/44104633/transforming-2d-image-coordinates-to-3d-world-coordinates-with-z-0
* https://github.com/IndrajeetDatta/Extrinsics
* http://answers.opencv.org/question/62779/image-coordinate-to-world-coordinate-opencv/
* https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point

## Usage
```
$ cmake .

-- The C compiler identification is GNU 6.3.0
...
-- Build files have been written to: /home/rodolfoap/OpenCV-2Dto3D

$ make

Scanning dependencies of target transform
[ 50%] Building CXX object CMakeFiles/transform.dir/main.cpp.o
[100%] Linking CXX executable transform
[100%] Built target transform

$ ./transform

Camera Matrix: [517.0036881709533, 0, 320;
 0, 517.0036881709533, 212;
 0, 0, 1]

Distortion Coefficients: [0.1128663679798094;
 -1.487790079922432;
 0;
 0;
 2.300571896761067]

Image Points: [275, 204;
 331, 204;
 331, 308;
 257, 308]

World Points: [0, 0, 0;
 1.775, 0, 0;
 1.775, 4.62, 0;
 0, 4.62, 0]

Rotation Matrix:
[0.9996846093770911, -0.01932780074441647, 0.01603489610059837;
 -0.002666758265168746, 0.5531906830965861, 0.8330503925546687;
 -0.02497138712462735, -0.8328304174641538, 0.5529646693700742]

Camera Coordinates:[331;
 308;
 1]

World Coordinates[1.77747, 4.62494, 0]
```
