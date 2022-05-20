cmake_minimum_required(VERSION 3.21)
project(physical_engine)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(physical_engine main.cpp Ball/Ball.cpp Ball/Ball.h object.cpp object.h)

target_link_libraries(physical_engine ${OpenCV_LIBS})
