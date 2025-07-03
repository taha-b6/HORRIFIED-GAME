cmake_minimum_required(VERSION 3.0)
project(HORRIFIED)
add_executable(app ./src/main.cpp ./src/card.cpp ./src/character.cpp ./src/etc.cpp ./src/monster_card.cpp ./src/moving.cpp ./src/place.cpp)
include_directories(./include)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

