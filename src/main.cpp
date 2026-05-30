#include <ctime>
#include <cstdlib>
#include "core/GameManager.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameManager::getInstance().run();

    return 0;
}