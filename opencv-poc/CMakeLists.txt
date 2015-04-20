cmake_minimum_required(VERSION 3.1)
project(opencv-poc)
find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(opencv-poc ${SOURCE_FILES} OpenCVWindow.cpp OpenCVWindow.h Stopwatch.cpp Stopwatch.h)
target_link_libraries( opencv-poc ${OpenCV_LIBS} )