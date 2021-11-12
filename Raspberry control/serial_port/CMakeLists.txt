  
cmake_minimum_required (VERSION 2.8.11)
project (serial_port C)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.c)


