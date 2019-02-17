#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

// https://stackoverflow.com/questions/51272055/opencv-unproject-2d-points-to-3d-with-known-depth-z
// https://stackoverflow.com/questions/44382267/how-to-find-the-focal-length-from-camera-matrix
// http://ksimek.github.io/2013/08/13/intrinsic/

std::vector<cv::Point2d> Project(const std::vector<cv::Point3d> &points,
				 const cv::Mat &intrinsic,
				 const cv::Mat &distortion) {
	std::vector<cv::Point2d> result;
	cv::projectPoints(points, cv::Mat(3, 1, CV_64F, cvScalar(0.)), cv::Mat(3, 1, CV_64F, cvScalar(0.)), intrinsic, distortion, result);
	return result;
}

std::vector<cv::Point3d> Unproject(const std::vector<cv::Point2d> &points,
				   const std::vector<double> &Z,
				   const cv::Mat &intrinsic,
				   const cv::Mat &distortion) {
	double f_x= intrinsic.at<double>(0, 0);
	double f_y= intrinsic.at<double>(1, 1);
	double c_x= intrinsic.at<double>(0, 2);
	double c_y= intrinsic.at<double>(1, 2);

	// Step 1. Undistort
	std::vector<cv::Point2d> points_undistorted;
	assert(Z.size() == 1 || Z.size() == points.size());
	if(!points.empty()) {
		cv::undistortPoints(points, points_undistorted, intrinsic, distortion, cv::noArray(), intrinsic);
	}

	// Step 2. Reproject
	std::vector<cv::Point3d> result;
	result.reserve(points.size());
	for(size_t idx= 0; idx < points_undistorted.size(); ++idx) {
		const double z= Z.size() == 1 ? Z[0] : Z[idx];
		result.push_back(cv::Point3d((points_undistorted[idx].x - c_x) / f_x * z,
					     (points_undistorted[idx].y - c_y) / f_y * z,
					     z));
	}
	return result;
}

int main() {
	const double f_x= 2800.; // in pixels
	const double f_y= 2800.; // in pixels
	const double c_x= 0960.; // in pixels
	const double c_y= 0540.; // in pixels

	const cv::Mat intrinsic = (cv::Mat_<double>(3, 3) << f_x, 0.0, c_x, 0.0, f_y, c_y, 0.0, 0.0, 1.0);
	const cv::Mat distortion= (cv::Mat_<double>(5, 1) << -0.32, 1.24, 0.0013, 0.0013);

	const cv::Point3d point_single(10.0, -2.0, 30.0);
	const cv::Point2d point_single_projected  = Project({point_single}, intrinsic, distortion)[0];
	const cv::Point3d point_single_unprojected= Unproject({point_single_projected}, {point_single.z}, intrinsic, distortion)[0];

	std::cout << "Expected: [" << point_single.x << " " << point_single.y << " " << point_single.z << "]" << std::endl;
	std::cout << "Computed: [" << point_single_unprojected.x << " " << point_single_unprojected.y << " " << point_single_unprojected.z << "]" << std::endl;
}
