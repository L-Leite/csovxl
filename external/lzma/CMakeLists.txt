cmake_minimum_required(VERSION 3.0)

project(lzma)

file(GLOB LZMA_SOURCES
    "LzmaDec.c"
    "7zTypes.h"
    "LzmaDec.h")

add_library(${PROJECT_NAME} STATIC ${LZMA_SOURCES})

set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(LZMA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(LZMA_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)
