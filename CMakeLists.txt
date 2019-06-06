# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(protobuf-examples)

# Find required protobuf package
find_package(Protobuf REQUIRED)

if(Protobuf_FOUND)
    message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

foreach(example add_people list_people)
    set(${example}_SRCS ${example}.cc)
    set(${example}_PROTOS addressbook.proto)

    # Code Generation
    # Generate addressbook.pb.h and addressbook.pb.cc in the legacy mode
    protobuf_generate_cpp(${example}_PROTO_SRCS ${example}_PROTO_HDRS ${${example}_PROTOS})

    # Executable name setup
    set(executable_name ${example}_cpp)

    # Build executables
    add_executable(${executable_name} ${${example}_SRCS} ${${example}_PROTO_SRCS} ${${example}_PROTO_HDRS} ${${example}_PROTOS})
    target_link_libraries(${executable_name} ${Protobuf_LIBRARIES})

endforeach()
