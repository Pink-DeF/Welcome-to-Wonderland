cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_executable(${PROJECT_NAME} main.cpp main/scene/cpp/mainMenu.cpp main/scene/cpp/jumpscare.cpp
	main/scene/cpp/labtop.cpp main/scene/cpp/door.cpp
	main/scene/cpp/office.cpp
	main/enemy/cpp/ErrorTime.cpp main/enemy/cpp/FoxDen.cpp
	main/enemy/cpp/MasterOfPuppet.cpp main/enemy/cpp/SpringTime.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
