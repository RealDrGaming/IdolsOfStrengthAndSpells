#include "Blade.h"
#include "../characters/Character.h"
#include <iostream>

Blade::Blade() : Item("Blade", 50) { }

void Blade::use(Character* myHero, Character* enemyHero)
{
    std::cout << "\n[Item] " << myHero->getName() << " used Blade! Their next attack will deal double damage." << std::endl;
    myHero->setBladeActive(true);
}