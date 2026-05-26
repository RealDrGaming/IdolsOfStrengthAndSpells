#include <print>

#include "Ray.h"
#include "../characters/Character.h"

Ray::Ray() : Item("Ray", 90) { }

void Ray::use(Character* myHero, Character* enemyHero)
{
    std::println("\n[Item] {} used Ray and shattered the Mirror!", myHero->getName());

    myHero->setMirrorActive(false);
}