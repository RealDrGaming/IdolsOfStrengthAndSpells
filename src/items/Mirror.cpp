#include "Mirror.h"
#include "../characters/Character.h"
#include <iostream>

Mirror::Mirror() : Item("Mirror", 80) { }

void Mirror::use(Character* myHero, Character* enemyHero)
{
    std::cout << "\n[Item] " << myHero->getName() << " cast a Mirror onto " << enemyHero->getName() << "!" << std::endl;
    std::cout << "Their next special ability is gonna be negated!" << std::endl;

    enemyHero->setMirrorActive(true); 
}