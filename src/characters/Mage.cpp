#include "Mage.h"
#include <cstdlib>
#include <iostream>

Mage::Mage(const std::string& name) : Character(name, 12) { }

void Mage::takeDamage(int amount)
{
    _currHp -= amount;

    if (_currHp < 0) _currHp = 0;
}

int Mage::calculateDamage() {
    int baseDamage = (std::rand() % 12) + 1;
    
    std::cout << "\n[Mage] " << _name << " will deal: " << baseDamage << "dmg" << std::endl;
    std::cout << "Do you want to activate Spell Magnification? "
                << "(Damage is transmuted by the formula: 12 - " << baseDamage << "dmg)? (y/n): ";
    
    char choice;
    std::cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        int newDamage = 12 - baseDamage;
        std::cout << "Spell Magnification was activated! Spell will now deal: " << newDamage << "dmg" << std::endl;
        return newDamage;
    }
    
    std::cout << "Spell was weak and will deal: " << baseDamage << "dmg" << std::endl;
    return baseDamage;
}