#pragma once

#include "Item.h"

class Shield : public Item
{
public:
    Shield();
    void use(Character* myHero, Character* enemyHero) override;
};