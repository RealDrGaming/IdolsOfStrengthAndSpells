#include "Warrior.h"
#include <cstdlib>
#include <algorithm>

Warrior::Warrior(const std::string& name) : Character(name, 20) { }

int Warrior::calculateDamage()
{
    return (std::rand() % 8) + 1;
}

void Warrior::takeDamage(int amount)
{
    int block = (std::rand() % 4) + 1;
    int actualDamage = amount - block;

    if (actualDamage < 0) actualDamage = 0;

    _currHp -= actualDamage;
}