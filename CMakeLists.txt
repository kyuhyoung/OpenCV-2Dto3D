cmake_minimum_required(VERSION 2.8)

PROJECT (transform)

find_package(OpenCV REQUIRED)

file(GLOB transform_SRCS
	"*.h"
	"*.cpp")
ADD_EXECUTABLE (transform ${transform_SRCS})

if (OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	include_directories("${OPENCV_CONFIG_PATH}/include")
	target_link_libraries(transform ${OpenCV_LIBS})
else (OpenCV_FOUND)
mesage("PB->OPENCV=${OpenCV_INCLUDE_DIRS}")
endif (OpenCV_FOUND)
