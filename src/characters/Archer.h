#pragma once
#include "Character.h"

class Archer : public Character {
public:
    Archer(const std::string& name);

    void takeDamage(int amount) override;
    int calculateDamage() override;
};