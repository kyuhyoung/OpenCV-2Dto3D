# OpenCV-2Dto3D


Based on:

* https://stackoverflow.com/questions/44104633/transforming-2d-image-coordinates-to-3d-world-coordinates-with-z-0
* https://github.com/IndrajeetDatta/Extrinsics
* http://answers.opencv.org/question/62779/image-coordinate-to-world-coordinate-opencv/
* https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point
* http://www.codinglabs.net/article_world_view_projection_matrix.aspx

## Usage
```
$ cmake .

-- The C compiler identification is GNU 6.3.0
...
-- Build files have been written to: /home/rodolfoap/OpenCV-2Dto3D

$ make

make.build 
-- The C compiler identification is GNU 6.3.0
-- The CXX compiler identification is GNU 6.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found OpenCV: /usr/local (found version "3.4.1") 
-- Configuring done
-- Generating done
-- Build files have been written to: /home/rodolfoap/git/OpenCV-2Dto3D/build
Scanning dependencies of target transform
Scanning dependencies of target genmatrix
[ 25%] Building CXX object CMakeFiles/transform.dir/transform.cpp.o
[ 50%] Building CXX object CMakeFiles/genmatrix.dir/genmatrix.cpp.o
[ 75%] Linking CXX executable transform
[100%] Linking CXX executable genmatrix
[100%] Built target transform
[100%] Built target genmatrix

$ ./genmatrix 

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

$ ./transform 275 204

Camera Matrix: [517.0036881709533, 0, 320;
 0, 517.0036881709533, 212;
 0, 0, 1]

Distortion Coefficients: [0.1128663679798094;
 -1.487790079922432;
 0;
 0;
 2.300571896761067]
Rotation Matrix: [0.9996846093770911, -0.01932780074441647, 0.01603489610059837;
 -0.002666758265168746, 0.5531906830965861, 0.8330503925546687;
 -0.02497138712462735, -0.8328304174641538, 0.5529646693700742]
Translation Vector: [-1.423470184607422;
 -0.2493082486757987;
 16.30654549944402]
Camera Coordinates:[275;
 204;
 1]

World Coordinates[0.003647, -0.00556071, 0]

[275,204] -> [0.003647,-0.00556071]
```
