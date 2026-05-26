#include <print>

#include "Shield.h"
#include "../characters/Character.h"

Shield::Shield() : Item("Shield", 100) { }

void Shield::use(Character* myHero, Character* enemyHero)
{
    std::println("\n[Item] {} raised a Shield. The next attack will deal no damage.", myHero->getName());
    myHero->setShieldActive(true);
}