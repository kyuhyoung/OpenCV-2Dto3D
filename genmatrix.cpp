// Taken from:
// https://stackoverflow.com/questions/44104633/transforming-2d-image-coordinates-to-3d-world-coordinates-with-z-0
// https://github.com/IndrajeetDatta/Extrinsics
// http://answers.opencv.org/question/62779/image-coordinate-to-world-coordinate-opencv/
// https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <cstdlib>

cv::Mat cameraMatrix, distCoeffs, rotationVector, rotationMatrix,
		translationVector, invR_x_invM_x_uv1, invR_x_tvec, wcPoint;
std::vector<cv::Point2d> image_points;
std::vector<cv::Point3d> world_points;
double Z;

int main(int argc, char *argv[]) {
	// Intrinsics is already calculated
	cv::FileStorage intrin("intrinsics.yml", cv::FileStorage::READ);
	cv::FileStorage points("pointssets.yml", cv::FileStorage::READ);
	cv::FileStorage extrin("extrinsics.yml", cv::FileStorage::WRITE);

	intrin["camera_matrix"] >> cameraMatrix;
	std::cerr << "Camera Matrix: " << cameraMatrix << std::endl << std::endl;

	intrin["distortion_coefficients"] >> distCoeffs;
	std::cerr << "Distortion Coefficients: " << distCoeffs << std::endl;
	std::cerr << std::endl;

	points["imagepoints"] >> image_points;
	std::cerr << "Image Points: " << image_points << std::endl << std::endl;

	points["worldpoints"] >> world_points;
	std::cerr << "World Points: " << world_points << std::endl << std::endl;
	std::cerr << std::endl;

	// ... in order to get our matrix!
	solvePnP(world_points, image_points, cameraMatrix, distCoeffs,
			rotationVector, translationVector);
	Rodrigues(rotationVector, rotationMatrix);
	std::cerr << "Rotation Matrix: " << std::endl;
	std::cerr << rotationMatrix << std::endl;
	std::cerr << std::endl;

	extrin << "rotationmatrix" << rotationMatrix;
	extrin << "translationvector" << translationVector;

	return 0;
}
