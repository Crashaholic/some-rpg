# https://hsf-training.github.io/hsf-training-cmake-webpage/03-cmakelists/index.html

cmake_minimum_required(VERSION 3.15)

project(some_rpg LANGUAGES CXX)
set(TARGET_NAME "some-rpg")

find_package(Curses REQUIRED)

set (all_SRCS 
    # "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/syswrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/mysysdef.h"
    "${PROJECT_SOURCE_DIR}/src/syswrap.h"
    
	"${PROJECT_SOURCE_DIR}/src/game/game.h"
    "${PROJECT_SOURCE_DIR}/src/game/game.cpp"
    "${PROJECT_SOURCE_DIR}/src/game/item.h"
    "${PROJECT_SOURCE_DIR}/src/game/stat.h"
    "${PROJECT_SOURCE_DIR}/src/game/uidgen.h"
    "${PROJECT_SOURCE_DIR}/src/game/serializable.h"
    "${PROJECT_SOURCE_DIR}/src/game/scene.h"
    "${PROJECT_SOURCE_DIR}/src/game/scenemanager.h"
    "${PROJECT_SOURCE_DIR}/src/game/scenemanager.cpp"

    "${PROJECT_SOURCE_DIR}/src/game/scenes/mainmenu.h"
    "${PROJECT_SOURCE_DIR}/src/game/scenes/mainmenu.cpp"
    "${PROJECT_SOURCE_DIR}/src/game/scenes/pregame.h"
    "${PROJECT_SOURCE_DIR}/src/game/scenes/pregame.cpp"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${TARGET_NAME} ${all_SRCS})
target_compile_features(
    ${TARGET_NAME} 
    PRIVATE 
    cxx_std_17
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        ${CURSES_INCLUDE_DIR}
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE 
        ${CURSES_LIBRARIES}
)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)


