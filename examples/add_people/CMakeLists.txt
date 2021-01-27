# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(add_people VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Find required protobuf package
find_package(Protobuf REQUIRED)

add_executable(${PROJECT_NAME} add_people.cc)
target_link_libraries(${PROJECT_NAME} PUBLIC addressbook ${Protobuf_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Protobuf_INCLUDE_DIRS})
