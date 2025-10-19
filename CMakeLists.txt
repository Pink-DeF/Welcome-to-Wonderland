cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
#find_package(SDL3_ttf REQUIRED CONFIG)
#find_package(SDL3_image REQUIRED CONFIG)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
#target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
