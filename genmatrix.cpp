// Taken from:
// https://stackoverflow.com/questions/44104633/transforming-2d-image-coordinates-to-3d-world-coordinates-with-z-0
// https://github.com/IndrajeetDatta/Extrinsics
// http://answers.opencv.org/question/62779/image-coordinate-to-world-coordinate-opencv/
// https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point
// http://www.codinglabs.net/article_world_view_projection_matrix.aspx

#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <cstdlib>

cv::Mat cameraMatrix, distCoeffs, rotationVector, rotationMatrix, translationVector, invR_x_invM_x_uv1, invR_x_tvec, wcPoint;
std::vector<cv::Point2d> image_points;
std::vector<cv::Point3d> world_points;
double Z;

int main(int argc, char *argv[]) {
	// Load intrinsics and points.
	cv::FileStorage intrin("intrinsics.yml", cv::FileStorage::READ);
	cv::FileStorage points("pointssets.yml", cv::FileStorage::READ);
	cv::FileStorage extrin("extrinsics.yml", cv::FileStorage::WRITE);
	intrin["camera_matrix"] >> cameraMatrix;
	intrin["distortion_coefficients"] >> distCoeffs;
	points["imagepoints"] >> image_points;
	points["worldpoints"] >> world_points;

	// Generate our matrix; rvec and tvec are the output.
	solvePnP(world_points, image_points, cameraMatrix, distCoeffs, rotationVector, translationVector);
	Rodrigues(rotationVector, rotationMatrix);

	// Save the results
	extrin << "rotationmatrix" << rotationMatrix;
	extrin << "translationvector" << translationVector;

	std::cerr << "Camera Matrix:" << std::endl << cameraMatrix << std::endl;
	std::cerr << "Distortion Coefficients: " << std::endl << distCoeffs << std::endl;
	std::cerr << "Image Points:" << std::endl << image_points << std::endl;
	std::cerr << "World Points:" << std::endl << world_points << std::endl;
	std::cerr << "Rotation Matrix:" << std::endl << rotationMatrix << std::endl;
	std::cerr <<  "Translation Vector:" << std::endl << translationVector << std::endl;

	return 0;
}
