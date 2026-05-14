cmake_minimum_required(VERSION 4.2)
project(IdolsOfStrengthAndSpells CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)
include_directories(src)

add_executable(IdolsOfStrengthAndSpells
        src/main.cpp
        src/Character.h)