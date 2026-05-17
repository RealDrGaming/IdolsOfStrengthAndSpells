#include "StoreManager.h"
#include <iostream>

#include "../characters/Warrior.h"
#include "../characters/Mage.h"
#include "../characters/Archer.h"
#include "../items/HealingPotion.h"
#include "../items/Blade.h"
#include "../items/Mirror.h"
#include "../items/Ray.h"
#include "../items/Shield.h"

StoreManager::StoreManager(User* customer) : _customer(customer) { }

void StoreManager::open()
{
    bool inStore = true;
    while (inStore)
    {
        std::cout << "\n=== STORE ===\n";
        std::cout << "Available XP: " << _customer->getAvailableXP() << "\n";
        std::cout << "1. Buy Item\n";
        std::cout << "2. Buy new Character (50 XP)\n";
        std::cout << "3. Level up existing Character (100 XP)\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "I choose: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) buyItem();
        else if (choice == 2) buyCharacter();
        else if (choice == 3) levelUpCharacter();
        else if (choice == 4) inStore = false;
    }
}

void StoreManager::buyItem()
{
    std::cout << "\n--- Item Purchase ---\n";
    std::cout << "Available XP: " << _customer->getAvailableXP() << "\n";
    std::cout << "1. Health Potion (30 XP)\n";
    std::cout << "2. Blade (50 XP)\n";
    std::cout << "3. Mirror (80 XP)\n";
    std::cout << "4. Ray (90 XP)\n";
    std::cout << "5. Shield (100 XP)\n";
    std::cout << "6. Back\n";
    std::cout << "I choose: ";

    int choice;
    std::cin >> choice;

    int cost = 0;
    if (choice == 1) cost = 30;
    else if (choice == 2) cost = 50;
    else if (choice == 3) cost = 80;
    else if (choice == 4) cost = 90;
    else if (choice == 5) cost = 100;
    else return;

    if (_customer->spendXP(cost))
    {
        switch (choice)
        {
            case 1: _customer->addItem(std::make_unique<HealingPotion>());
                break;
            case 2: _customer->addItem(std::make_unique<Blade>());
                break;
            case 3: _customer->addItem(std::make_unique<Mirror>());
                break;
            case 4: _customer->addItem(std::make_unique<Ray>());
                break;
            case 5: _customer->addItem(std::make_unique<Shield>());
                break;
        }
        std::cout << "Purchase of Item successful!\n";
    }
    else
    {
        std::cout << "Not enough XP!\n";
    }
}

void StoreManager::buyCharacter()
{
    std::cout << "\n--- Character Purchase ---\n";
    if (_customer->spendXP(50))
    {
        std::cout << "Successfully spent 50XP on new Character!. ";
        _customer->addCharacter(createCharacterForSale());
        std::cout << "The Character is added in your profile!\n";
    }
    else
    {
        std::cout << "Not enough XP (Required - 50XP)!\n";
    }
}

std::unique_ptr<Character> StoreManager::createCharacterForSale()
{
    int choice = 0;
    std::string charName;

    std::cout << "1. Warrior (20 HP, d8 dmg, Block)\n";
    std::cout << "2. Mage (12 HP, d12 dmg, Spell Magnification)\n";
    std::cout << "3. Archer (15 HP, d8 dmg, Poison Arrow)\n";
    std::cout << "I choose: ";
    std::cin >> choice;

    std::cout << "My character's name is: ";
    std::cin >> charName;

    switch (choice)
    {
        case 1: return std::make_unique<Warrior>(charName);
        case 2: return std::make_unique<Mage>(charName);
        case 3: return std::make_unique<Archer>(charName);
        default:
            std::cout << "Invalid choice. Defaulting to Warrior.\n";
            return std::make_unique<Warrior>(charName);
    }
}

void StoreManager::levelUpCharacter()
{
    std::cout << "\n--- Levelling Up of Character ---\n";
    const auto& characters = _customer->getCharacters();
    
    if (characters.empty())
    {
        std::cout << "You don't have any Characters!\n";
        return;
    }

    std::cout << "Choose Character:\n";
    for (size_t i = 0; i < characters.size(); ++i)
    {
        std::cout << i + 1 << ". " << characters[i]->getName() 
                    << " (Level " << characters[i]->getLevel()
                    << ", HP: " << characters[i]->getMaxHP() << ")\n";
    }
    
    int charChoice;
    std::cin >> charChoice;
    
    if (charChoice < 1 || charChoice > static_cast<int>(characters.size()))
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    if (_customer->spendXP(100)) {
        std::cout << "\nChoose level up stat increase:\n";
        std::cout << "1. Increase max HP by 2\n";
        std::cout << "2. Increase max DMG by 1\n";
        std::cout << "I choose: ";
        
        int bonusChoice;
        std::cin >> bonusChoice;
        
        Character* selectedChar = characters[charChoice - 1].get();
        
        if (bonusChoice == 1)
        {
            selectedChar->levelUpMaxHealth();
            std::cout << selectedChar->getName() << " now has " << selectedChar->getMaxHP() << " maximum HP!\n";
        }
        else if (bonusChoice == 2)
        {
            selectedChar->levelUpMaxDamage();
            std::cout << selectedChar->getName() << " now deals more DMG!\n";
        }
        else
        {
            std::cout << "Invalid choice. Defaulting to maximum HP increase.\n";
            selectedChar->levelUpMaxHealth();
        }
    }
    else
    {
        std::cout << "Not enough XP (Required 100 XP)!\n";
    }
}