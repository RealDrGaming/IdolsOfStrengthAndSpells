#include "Ray.h"
#include "../characters/Character.h"
#include <iostream>

Ray::Ray() : Item("Ray", 90) { }

void Ray::use(Character* myHero, Character* enemyHero)
{
    std::cout << "\n[Item] " << myHero->getName() << " used Ray and shattered the Mirror!" << std::endl;

    myHero->setMirrorActive(false);
}