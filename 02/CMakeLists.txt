cmake_minimum_required(VERSION 2.8)
project(opencv_02)
find_package(OpenCV REQUIRED)
add_executable(opencv_02 opencv_02.cpp)
target_link_libraries(opencv_02 ${OpenCV_LIBS})
