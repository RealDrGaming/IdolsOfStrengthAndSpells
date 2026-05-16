#pragma once

#include "Item.h"

class Mirror : public Item
{
public:
    Mirror();
    void use(Character* myHero, Character* enemyHero) override;
};