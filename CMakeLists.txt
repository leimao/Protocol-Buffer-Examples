# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(protobuf-examples)

# Find required protobuf package
# find_package(protobuf CONFIG REQUIRED) # This does not work
find_package(Protobuf REQUIRED)

if(protobuf_VERBOSE)
    message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Microsoft Visual C++ Compatibility
# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach()
endif()

foreach(example add_people list_people)
    set(${example}_SRCS ${example}.cc)
    set(${example}_PROTOS addressbook.proto)

    # Code Generation
    # Generate addressbook.pb.h and addressbook.pb.cc
    if(protobuf_MODULE_COMPATIBLE) # Legacy Mode
        protobuf_generate_cpp(${example}_PROTO_SRCS ${example}_PROTO_HDRS ${${example}_PROTOS})
        list(APPEND ${example}_SRCS ${${example}_PROTO_SRCS} ${${example}_PROTO_HDRS})
    endif()

    #Executable setup
    set(executable_name ${example}_cpp)
    add_executable(${executable_name} ${${example}_SRCS} ${${example}_PROTOS})
    if(protobuf_MODULE_COMPATIBLE) # Legacy Mode
        target_include_directories(${executable_name} PUBLIC ${PROTOBUF_INCLUDE_DIRS})
        target_link_libraries(${executable_name} ${PROTOBUF_LIBRARIES})
    else()
        target_link_libraries(${executable_name} protobuf::libprotobuf)
        protobuf_generate(TARGET ${executable_name})
    endif()
endforeach()
