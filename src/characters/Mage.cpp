#include <cstdlib>
#include <print>

#include "Mage.h"

#include "../utils/Input.h"

Mage::Mage(const std::string& name) : Character(name, 12, 12) { }

void Mage::takeDamage(int amount)
{
    _currHp -= amount;

    if (_currHp < 0) _currHp = 0;
}

int Mage::calculateDamage()
{
    int baseDamage = (std::rand() % _maxDamage) + 1;
    
    std::println("\n[Mage] {} will deal: {}dmg", _name, baseDamage);
    std::print("Do you want to activate Spell Magnification? (Damage transmuted to 12 - {}dmg)? (y/n): ", baseDamage);
    std::fflush(stdout);

    if (Input::getYesNo())
    {
        int newDamage = 12 - baseDamage;
        std::println("Spell Magnification activated! Spell will now deal: {}dmg", newDamage);
        return newDamage;
    }

    std::println("Spell was weak and will deal: {}dmg", baseDamage);
    return baseDamage;
}