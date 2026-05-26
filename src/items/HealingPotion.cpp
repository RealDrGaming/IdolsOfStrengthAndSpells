#include <cstdlib>
#include <print>

#include "HealingPotion.h"
#include "../characters/Character.h"

HealingPotion::HealingPotion() : Item("Healing Potion", 30) { }

void HealingPotion::use(Character* myHero, Character* enemyHero)
{
    int healAmount = (std::rand() % 6) + 5;

    std::println("\nA Healing Potion was used!");
    std::println("{} was healed for {} HP.", myHero->getName(), healAmount);

    myHero->heal(healAmount);

    std::println("Current HP: {} / {}", myHero->getCurrentHP(), myHero->getMaxHP());
}