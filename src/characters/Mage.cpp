#include <cstdlib>
#include <print>
#include <algorithm>

#include "Mage.h"

#include "../utils/Input.h"

Mage::Mage(const std::string& name) : Character(name, 12, 12) { }

int Mage::calculateDamage()
{
    int baseDamage = (std::rand() % _maxDamage) + 1;
    int mult = this->hasBladeActive() ? 2 : 1;

    std::println("\n[Mage] {} rolled a base damage of {}!", _name, baseDamage);

    if (this->hasBladeActive())
    {
        std::println(">>> Blade is active! Base damage will be multiplied by {}!", mult);
    }

    int standardDamage = baseDamage * mult;
    int potentialDamage = std::max(0, (12 - baseDamage)) * mult;

    std::println("Standard attack will deal: {}dmg", standardDamage);
    std::print("Activate Spell Magnification? (Base: {} Becomes {}. Total with multipliers: {}dmg)? (y/n): ",
               baseDamage, 12 - baseDamage, potentialDamage);
    std::fflush(stdout);

    int finalDamage = standardDamage;

    if (Input::getYesNo())
    {
        if (this->hasMirrorActive())
        {
            std::println(">>> {} is affected by a Mirror! The Spell Magnification is blocked!", _name);
            this->setMirrorActive(false);
        }
        else
        {
            std::println("Spell Magnification activated! Spell will now deal: {}dmg", potentialDamage);
            finalDamage = potentialDamage;
        }
    }
    else
    {
        std::println("Spell was weak and will deal: {}dmg", standardDamage);
    }

    if (this->hasBladeActive()) this->setBladeActive(false);
    return finalDamage;
}