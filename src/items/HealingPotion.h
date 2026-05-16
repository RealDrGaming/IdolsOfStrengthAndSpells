#pragma once

#include "Item.h"

class HealingPotion : public Item
{
public:
    HealingPotion();

    void use(Character* myHero, Character* enemyHero) override;
};