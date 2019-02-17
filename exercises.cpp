#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
std::vector<cv::Point2d> Project(const std::vector<cv::Point3d> &points,
				 const cv::Mat &intrinsic,
				 const cv::Mat &distortion,
				 const cv::Mat &rotationVector,
				 const cv::Mat &translationVector) {
	std::vector<cv::Point2d> result;
	cv::projectPoints(points, rotationVector, translationVector, intrinsic, distortion, result);
	return result;
}
int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [u v]" << std::endl;
		return 0;
	}
	/**
	 *
	 * INTRINSICS
	 *
	 */
	cv::Mat intrinsics, distortion, rotationVector, rotationMatrix, translationVector;
	std::vector<cv::Point2d> image_points;
	std::vector<cv::Point3d> world_points;

	// Load intrinsics and points.
	cv::FileStorage intrsx("intrinsics.yml", cv::FileStorage::READ);
	cv::FileStorage points("pointssets.yml", cv::FileStorage::READ);
	cv::FileStorage extrsx("extrinsics.yml", cv::FileStorage::WRITE);
	intrsx["camera_matrix"] >> intrinsics;
	intrsx["distortion_coefficients"] >> distortion;
	points["worldpoints"] >> world_points;
	points["imagepoints"] >> image_points;

	// Generate our matrix; rvec and tvec are the output.
	solvePnP(world_points, image_points, intrinsics, distortion, rotationVector, translationVector);
	Rodrigues(rotationVector, rotationMatrix);

	// Save the results
	extrsx << "rotationMatrix" << rotationMatrix;
	extrsx << "rotationVector" << rotationVector;
	extrsx << "translationVector" << translationVector;

	std::cerr << "Intrinsics:" << intrinsics << std::endl;
	std::cerr << "Distortion:" << distortion << std::endl;
	std::cerr << "World_Pnts:" << world_points << std::endl;
	std::cerr << "Image_Pnts:" << image_points << std::endl;
	std::cerr << "rotationMatrix:" << rotationMatrix << std::endl;
	std::cerr << "rotationVector:" << rotationVector << std::endl;
	std::cerr << "translationVector:" << translationVector << std::endl;

	/**
	 *
	 * EXTRINSICS
	 *
	 */
	// cv::Mat screenCoordinates	 = cv::Mat::ones(3, 1, cv::DataType<double>::type);
	// screenCoordinates.at<double>(0, 0)= atoi(argv[1]);
	// screenCoordinates.at<double>(1, 0)= atoi(argv[2]);
	// screenCoordinates.at<double>(2, 0)= 1; // f=1

	// // Hypothesis ground:
	// double Z= 0;
	//
	// cv::Mat invR_x_invM_x_uv1, invR_x_tvec, wcPoint;
	// // s and point calculation, described here:
	// // https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point
	// invR_x_invM_x_uv1= rotationMatrix.inv() * intrinsics.inv() * screenCoordinates;
	// invR_x_tvec      = rotationMatrix.inv() * translationVector;
	// wcPoint		 = (Z + invR_x_tvec.at<double>(2, 0)) / invR_x_invM_x_uv1.at<double>(2, 0) * invR_x_invM_x_uv1 - invR_x_tvec;
	// //wcPoint= invR_x_invM_x_uv1 - invR_x_tvec;
	// cv::Point3f worldCoordinates(wcPoint.at<double>(0, 0), wcPoint.at<double>(1, 0), wcPoint.at<double>(2, 0));
	//
	// std::cerr << "Camera Coordinates:" << screenCoordinates << std::endl;
	// std::cerr << "World Coordinates: " << worldCoordinates << std::endl;
	// std::cout << "[" << screenCoordinates.at<double>(0, 0) << ", "
	// 	  << screenCoordinates.at<double>(1, 0) << "] -> ["
	// 	  << worldCoordinates.x << ", "
	// 	  << worldCoordinates.y << "]"
	// 	  << std::endl;

	const cv::Point2d point_single_projected= Project(world_points[0], intrinsics, distortion, rotationVector, translationVector)[0];
	std::cout << "Computed: " << point_single_projected << std::endl;

	return 0;
}
