#pragma once

#include "Item.h"

class Blade : public Item
{
public:
    Blade();
    void use(Character* myHero, Character* enemyHero) override;
};