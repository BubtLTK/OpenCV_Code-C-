cmake_minimum_required(VERSION 2.8)
project(opencv_06)
find_package(OpenCV REQUIRED)
add_executable(opencv_06 opencv_06.cpp)
target_link_libraries(opencv_06 ${OpenCV_LIBS})
