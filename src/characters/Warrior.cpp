#include "Warrior.h"
#include <cstdlib>
#include <print>

Warrior::Warrior(const std::string& name) : Character(name, 20, 8) { }

int Warrior::calculateDamage()
{
    int baseDamage = (std::rand() % _maxDamage) + 1;
    int mult = this->hasBladeActive() ? 2 : 1;

    if (this->hasMirrorActive())
    {
        std::println(">>> {} is a Warrior! The Mirror shatters uselessly against their raw strength!", _name);
        this->setMirrorActive(false);
    }

    std::println("\n[Warrior] {} rolled a base damage of {}!", _name, baseDamage);

    if (this->hasBladeActive())
    {
        std::println(">>> Blade is active! Base damage will be multiplied by {}!", mult);
    }

    int finalDamage = baseDamage * mult;
    std::println("Warrior will deal: {}dmg", finalDamage);

    if (this->hasBladeActive()) this->setBladeActive(false);

    return finalDamage;
}

int Warrior::calculateDefense()
{
    int block = (std::rand() % 4) + 1;
    std::println(">>> Warrior passive: {} blocks {} damage!", _name, block);
    return block;
}