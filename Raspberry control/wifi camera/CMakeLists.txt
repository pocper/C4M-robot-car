  
cmake_minimum_required (VERSION 2.8.11)
project (OpenCV)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
add_executable(${PROJECT_NAME} main.cpp)