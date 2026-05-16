#include "HealingPotion.h"
#include "../characters/Character.h"
#include <cstdlib>
#include <iostream>

HealingPotion::HealingPotion() : Item("Healing Potion", 30) { }

void HealingPotion::use(Character* myHero, Character* enemyHero)
{
    int healAmount = (std::rand() % 6) + 5;

    std::cout << "\nA Healing Potion was used!" << std::endl;
    std::cout << myHero->getName() << " was healed for " << healAmount << " HP." << std::endl;

    myHero->heal(healAmount);

    std::cout << "Current HP: " << myHero->getCurrentHP() << " / " << myHero->getMaxHP() << std::endl;
}