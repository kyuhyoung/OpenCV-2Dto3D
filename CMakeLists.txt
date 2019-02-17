cmake_minimum_required(VERSION 2.8)

PROJECT (transform)

ADD_EXECUTABLE (transform transform.cpp)
ADD_EXECUTABLE (genmatrix genmatrix.cpp)
ADD_EXECUTABLE (simpletfx simpletfx.cpp)
ADD_EXECUTABLE (exercises exercises.cpp)

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	include_directories("${OPENCV_CONFIG_PATH}/include")
	target_link_libraries(transform ${OpenCV_LIBS})
	target_link_libraries(genmatrix ${OpenCV_LIBS})
	target_link_libraries(simpletfx ${OpenCV_LIBS})
	target_link_libraries(exercises ${OpenCV_LIBS})
endif (OpenCV_FOUND)
