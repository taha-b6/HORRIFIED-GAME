cmake_minimum_required(VERSION 3.0)
project(HORRIFIED)
add_executable(app ./src/card.cpp ./src/character.cpp ./src/etc.cpp ./src/monster_card.cpp ./src/moving.cpp ./src/place.cpp ./src/main.cpp)
include_directories(./include)