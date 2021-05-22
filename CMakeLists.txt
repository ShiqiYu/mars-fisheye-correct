cmake_minimum_required(VERSION 3.0)
project( fisheye-correct )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( fisheye-correct fisheye-correct.cpp )
target_link_libraries( fisheye-correct ${OpenCV_LIBS} )

add_executable( fisheye-correct-video fisheye-correct-video.cpp )
target_link_libraries( fisheye-correct-video ${OpenCV_LIBS} )
