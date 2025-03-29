cmake_minimum_required(VERSION 3.24...3.30)
project(minesweeper)

include(FetchContent)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Our Project
set(SOURCE_FILES src/main.c src/minesweeper.c)
set(HEADER_FILES src/minesweeper.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL")
endif()
