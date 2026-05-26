#include <print>

#include "Blade.h"
#include "../characters/Character.h"

Blade::Blade() : Item("Blade", 50) { }

void Blade::use(Character* myHero, Character* enemyHero)
{
    std::println("\n[Item] {} used Blade! Their next attack will deal double damage.", myHero->getName());
    myHero->setBladeActive(true);
}