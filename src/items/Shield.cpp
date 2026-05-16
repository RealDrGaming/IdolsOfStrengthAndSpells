#include "Shield.h"
#include "../characters/Character.h"
#include <iostream>

Shield::Shield() : Item("Shield", 100) { }

void Shield::use(Character* myHero, Character* enemyHero)
{
    std::cout << "\n[Item] " << myHero->getName() << " raised a Shield. The next attack will deal no damage." << std::endl;
    myHero->setShieldActive(true);
}