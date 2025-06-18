cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME Snake)

project(
  ${PROJECT_NAME}
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_IMAGE REQUIRED CONFIG)
find_package(SDL3_TTF REQUIRED CONFIG)

message(STATUS "Found SDL3 version: ${SDL3_VERSION}")
message(STATUS "Found SDL3_image version: ${SDL3_image_VERSION}")
message(STATUS "Found SDL3_ttf_version: ${SDL3_ttf_VERSION}")

set(SOURCE_FILES src/main.cpp src/window.cpp src/game.cpp src/renderer.cpp
src/input_handler.cpp src/commands.cpp src/snake.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(Snake PRIVATE SDL3::SDL3 SDL3_image::SDL3_image
                                    SDL3_ttf::SDL3_ttf)
