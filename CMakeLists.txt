cmake_minimum_required(VERSION 3.10)
project(Car_Ros_serie)


find_package(OpenCV 2.4 REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Concurrent Test OpenGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(Traitement_Image src/image_analysis.cpp src/imgUtils.cpp src/imgUtils.h)
target_link_libraries( Traitement_Image ${OpenCV_LIBS} )
include_directories(${OpenCV_INCLUDE_DIRS})

