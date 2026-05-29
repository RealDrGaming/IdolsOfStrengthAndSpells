#pragma once

#include "Character.h"

class Archer : public Character
{
public:
    Archer(const std::string& name);

    int calculateDamage() override;
};