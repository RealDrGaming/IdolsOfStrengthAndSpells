#include <cstdlib>
#include <iostream>
#include <print>

#include "Archer.h"

#include "../utils/Input.h"

Archer::Archer(const std::string& name) : Character(name, 15, 8) { }

void Archer::takeDamage(int amount)
{
    _currHp -= amount;

    if (_currHp < 0) _currHp = 0;
}

int Archer::calculateDamage()
{
    int baseDamage = (std::rand() % _maxDamage) + 1;

    if (baseDamage >= 1 && baseDamage <= 4)
    {
        std::println("\n[Archer] {} will deal: {}dmg", _name, baseDamage);
        std::print("Do you want to use Poison Arrow and double the damage dealt? (y/n): ");
        std::fflush(stdout);

        if (Input::getYesNo())
        {
            int newDamage = baseDamage * 2;
            std::println("Poison Arrow was activated! Damage will now be: {}dmg", newDamage);
            return newDamage;
        }
    }
    else
    {
        std::println("\n[Archer] {} will deal: {}", _name, baseDamage);
        std::println("Damage is above 4, Poison Arrow cannot be activated!");
    }

    return baseDamage;
}