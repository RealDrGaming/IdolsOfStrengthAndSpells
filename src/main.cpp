#include <iostream>
#include <ctime>
#include <cstdlib>
#include "characters/Warrior.h"
#include "characters/Archer.h"
#include "characters/Mage.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Archer myCharacter("Petio");

    std::cout << "- Info about character -" << std::endl;
    std::cout << "Name: " << myCharacter.getName() << std::endl;
    std::cout << "Curr HP: " << myCharacter.getCurrentHP() << " / " << myCharacter.getMaxHP() << std::endl;
    std::cout << "Level: 1" << std::endl;

    std::cout << "\n-Attack test -" << std::endl;
    int damage = myCharacter.calculateDamage();
    std::cout << "Attack " << i + 1 << ": " << myCharacter.getName()
                << " deals " << damage << " dmg." << std::endl;

    std::cout << "\n- Defense test -" << std::endl;
    int incomingAttack = 10;
    std::cout << "opp attack deals: " << incomingAttack << " dmg." << std::endl;

    int hpBefore = myCharacter.getCurrentHP();
    myCharacter.takeDamage(incomingAttack);
    int hpAfter = myCharacter.getCurrentHP();
    int actualDamageTaken = hpBefore - hpAfter;

    std::cout << "actual dmg: " << actualDamageTaken << std::endl;
    std::cout << "HP now: " << myCharacter.getCurrentHP() << std::endl;

    std::cout << "\n- Heal test -" << std::endl;
    myCharacter.heal(5);
    std::cout << "HP after 5hp heal: " << myCharacter.getCurrentHP() << std::endl;

    if (myCharacter.isAlive())
    {
        std::cout << "\n" << myCharacter.getName() << " is alive and well!" << std::endl;
    }

    return 0;
}