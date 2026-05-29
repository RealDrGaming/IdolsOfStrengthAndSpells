#pragma once

#include "Character.h"

class Mage : public Character
{
public:
    Mage(const std::string& name);

    int calculateDamage() override;
};