# https://hsf-training.github.io/hsf-training-cmake-webpage/03-cmakelists/index.html

cmake_minimum_required(VERSION 3.15)

project(some-rpg)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

file (GLOB all_SRCS 
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

set(TARGET_NAME "some-rpg")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_definitions(__unix__)
add_executable(${TARGET_NAME} ${all_SRCS})
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_NAME} ${CURSES_LIBRARIES})

