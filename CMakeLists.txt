# Top-Level CmakeLists.txt
cmake_minimum_required(VERSION 2.8)

PROJECT( zeroak )
# The version number.

#version MAJOR.MINOR.PATCH
set (CMAKE_VERSION_MAJOR 0)
set (CMAKE_VERSION_MINOR 1)
set (CMAKE_PATCH_VERSION 0)


set (zeroak_SHAREDIR ${CMAKE_ROOT}/bialk/zeroak)


# configure a header file to pass some of the CMake settings
# to the source code
#CONFIGURE_FILE(
#  "${PROJECT_SOURCE_DIR}/configzeroak.h.in"
#  "${PROJECT_BINARY_DIR}/configzeroak.h"
#  )

# add the binary tree to the search path for include files
# so that we will find configzeroapp.h
include_directories("${PROJECT_BINARY_DIR}")

#SET ( CMAKE_BUILD_TYPE Release )
SET ( CMAKE_BUILD_TYPE Debug )

ADD_SUBDIRECTORY( gui )
