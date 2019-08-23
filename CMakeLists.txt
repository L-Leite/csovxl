cmake_minimum_required(VERSION 3.12.0)

project(csovxl LANGUAGES CXX)

#
# User optinos
#
option(VXL_USE_CLANG_FSAPI "Use libc++fs when available" OFF)

#
# Global paths
#
set(VXL_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(VXL_LIBS_DIR "${VXL_ROOT_DIR}/external")

set(VXL_LIB_GSL_DIR "${VXL_LIBS_DIR}/gsl-lite")
set(VXL_LIB_LZMA_DIR "${VXL_LIBS_DIR}/lzma")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#
# Dependencies
#
add_subdirectory("${VXL_LIB_LZMA_DIR}")

#
# add source files to the project
#
set(VXL_SOURCES_BASE
    "sources/cmdparser.cpp"
    "sources/fsutils.cpp"
    "sources/main.cpp"
    "sources/vxl_lzma.cpp")

set(VXL_HEADERS_BASE
    "headers/cmdparser.hpp"
    "headers/fsutils.hpp"
    "headers/vxl_lzma.hpp")

file(GLOB VXL_ALL_SOURCES
    ${VXL_SOURCES_BASE}
    ${VXL_HEADERS_BASE})

source_group("Source Files" FILES ${VXL_SOURCES_BASE})
source_group("Header Files" FILES ${VXL_HEADERS_BASE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

#
# Add executable to build.
#
add_executable(csovxl ${VXL_ALL_SOURCES})

#
# Enable all warnings
#
if(MSVC)
  target_compile_options(csovxl PRIVATE /W4)
else()
  target_compile_options(csovxl PRIVATE -Wall -Wextra -pedantic)
endif()

#
# Setup include directories
#
target_include_directories(csovxl PRIVATE "headers")

target_include_directories(csovxl PRIVATE
    "${LZMA_INCLUDE_DIR}")

#
# Setup library directories
#
if(VXL_USE_CLANG_FSAPI)
    target_link_libraries(csovxl c++fs)
elseif(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_link_libraries(csovxl stdc++fs)
endif()

target_include_directories(csovxl PRIVATE
    "${VXL_LIB_GSL_DIR}/include")

target_link_libraries(csovxl lzma)

