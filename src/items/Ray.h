#pragma once

#include "Item.h"

class Ray : public Item
{
public:
    Ray();
    void use(Character* myHero, Character* enemyHero) override;
};