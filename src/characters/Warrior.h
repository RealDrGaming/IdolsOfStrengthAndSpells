#pragma once

#include "Character.h"

class Warrior : public Character
{
public:
    Warrior(const std::string& name);

    void takeDamage(int amount) override;
    int calculateDamage() override;
};