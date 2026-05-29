#include <cstdlib>
#include <iostream>
#include <print>

#include "Archer.h"

#include "../utils/Input.h"

Archer::Archer(const std::string& name) : Character(name, 15, 8) { }

int Archer::calculateDamage()
{
    int baseDamage = (std::rand() % _maxDamage) + 1;
    int mult = this->hasBladeActive() ? 2 : 1;

    if (this->hasMirrorActive())
    {
        std::println(">>> {} is affected by a Mirror! Special active abilities are blocked!", _name);
        this->setMirrorActive(false);

        if (this->hasBladeActive()) this->setBladeActive(false);
        return baseDamage * mult;
    }

    std::println("\n[Archer] {} rolled a base damage of {}!", _name, baseDamage);

    if (this->hasBladeActive())
    {
        std::println(">>> Blade is active! Base damage will be multiplied by {}!", mult);
    }

    int standardDamage = baseDamage * mult;
    int finalDamage = standardDamage;

    if (baseDamage >= 1 && baseDamage <= 4)
    {
        int poisonDamage = (baseDamage * 2) * mult;

        std::println("Standard attack will deal: {}dmg", standardDamage);
        std::print("Activate Poison Arrow? (Base {} becomes {}, total with multipliers: {}dmg)? (y/n): ",
                   baseDamage, baseDamage * 2, poisonDamage);
        std::fflush(stdout);

        if (Input::getYesNo())
        {
            std::println("Poison Arrow was activated! Damage will now be: {}dmg", poisonDamage);
            finalDamage = poisonDamage;
        }
        else
        {
            std::println("Standard attack will deal: {}dmg", standardDamage);
        }
    }
    else
    {
        std::println("Standard attack will deal: {}dmg", standardDamage);
        std::println("Base damage is above 4, Poison Arrow cannot be activated!");
    }

    if (this->hasBladeActive()) this->setBladeActive(false);
    return finalDamage;
}