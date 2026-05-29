#pragma once

#include "Character.h"

class Warrior : public Character
{
public:
    Warrior(const std::string& name);
    
    int calculateDamage() override;
    int calculateDefense() override;
};