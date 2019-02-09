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
	if (argc < 2) { std::cerr << "Usage: " << argv[0] << " [u v]" << std::endl; return 0; }
	cv::Mat screenCoordinates = cv::Mat::ones(3, 1, cv::DataType<double>::type);
	screenCoordinates.at<double>(0, 0) = atoi(argv[1]);
	screenCoordinates.at<double>(1, 0) = atoi(argv[2]);
	screenCoordinates.at<double>(2, 0) = 1; // f=1

	// Load matrix
	cv::FileStorage intrin("intrinsics.yml", cv::FileStorage::READ);
	cv::FileStorage extrin("extrinsics.yml", cv::FileStorage::READ);
	intrin["camera_matrix"] >> cameraMatrix;
	intrin["distortion_coefficients"] >> distCoeffs;
	extrin["rotationmatrix"] >> rotationMatrix;
	extrin["translationvector"] >> translationVector;

	// Hypothesis ground:
	Z = 0;

	// s and point calculation, described here:
	// https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point
	invR_x_invM_x_uv1 = rotationMatrix.inv() * cameraMatrix.inv() * screenCoordinates;
	invR_x_tvec = rotationMatrix.inv() * translationVector;
	wcPoint = (Z + invR_x_tvec.at<double>(2, 0)) / invR_x_invM_x_uv1.at<double>(2, 0) * invR_x_invM_x_uv1 - invR_x_tvec;
	//wcPoint = invR_x_invM_x_uv1 - invR_x_tvec;
	cv::Point3f worldCoordinates(wcPoint.at<double>(0, 0), wcPoint.at<double>(1, 0), wcPoint.at<double>(2, 0));

	std::cerr << "Camera Coordinates:" << screenCoordinates << std::endl << std::endl;
	std::cerr << "World Coordinates: " << worldCoordinates  << std::endl << std::endl;
	std::cout << "[" << screenCoordinates.at<double>(0, 0) << ","
			 << screenCoordinates.at<double>(1, 0) << "] -> ["
			 << worldCoordinates.x << "," << worldCoordinates.y << "]"
			 << std::endl;
	return 0;
}
