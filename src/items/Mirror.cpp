#include <print>

#include "Mirror.h"
#include "../characters/Character.h"

Mirror::Mirror() : Item("Mirror", 80) { }

void Mirror::use(Character* myHero, Character* enemyHero)
{
    std::println("\n[Item] {} cast a Mirror onto {}!", myHero->getName(), enemyHero->getName());
    std::println("Their next special ability is gonna be negated!");

    enemyHero->setMirrorActive(true); 
}