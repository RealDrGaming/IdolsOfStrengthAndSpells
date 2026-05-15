cmake_minimum_required(VERSION 4.2)
project(IdolsOfStrengthAndSpells CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)
include_directories(src)

add_executable(IdolsOfStrengthAndSpells
        src/main.cpp
        src/characters/Character.h
        src/characters/Character.cpp
        src/utils/Serializer.cpp
        src/utils/Serializer.h
        src/core/GameManager.cpp
        src/core/GameManager.h
        src/items/Item.cpp
        src/items/Item.h
        src/characters/Warrior.cpp
        src/characters/Warrior.h
        src/characters/Mage.cpp
        src/characters/Mage.h
        src/characters/Archer.cpp
        src/characters/Archer.h)