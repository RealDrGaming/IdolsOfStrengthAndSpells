#pragma once
#include "Character.h"

class Mage : public Character {
public:
    Mage(const std::string& name);

    void takeDamage(int amount) override;
    int calculateDamage() override;
};