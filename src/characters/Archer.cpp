#include "Archer.h"
#include <cstdlib>
#include <iostream>

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
        std::cout << "\n[Archer] " << _name << " will deal: " << baseDamage << "dmg" << std::endl;
        std::cout << "Do you want to use Poison Arrow and double the damage dealt? (y/n): ";
        
        char choice;
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y')
        {
            int newDamage = baseDamage * 2;
            std::cout << "Poison Arrow was activated! Damage will now be: " << newDamage << "dmg" << std::endl;
            return newDamage;
        }
    }
    else
    {
        std::cout << "\n[Archer] " << _name << " will deal: " << baseDamage << std::endl;
        std::cout << "Damage is above 4, Poison Arrow cannot be activated!" << std::endl;
    }

    return baseDamage;
}