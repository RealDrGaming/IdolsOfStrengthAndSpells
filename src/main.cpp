#include <iostream>
#include <ctime>
#include <cstdlib>
#include "core/GameManager.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameManager gameManager;

    gameManager.run();

    return 0;
}