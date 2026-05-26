#include <print>
#include <cstdio>

#include "StoreManager.h"
#include "../utils/Input.h"

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
        std::println("\n=== STORE ===");
        std::println("Available XP: {}", _customer->getAvailableXP());
        std::println("1. Buy Item");
        std::println("2. Buy new Character (50 XP)");
        std::println("3. Level up existing Character (100 XP)");
        std::println("4. Back to Main Menu");
        std::print("I choose: ");
        std::fflush(stdout);

        int choice = Input::getInt(1, 4);

        if (choice == 1) buyItem();
        else if (choice == 2) buyCharacter();
        else if (choice == 3) levelUpCharacter();
        else if (choice == 4) inStore = false;
    }
}

void StoreManager::buyItem()
{
    std::println("\n--- Item Purchase ---");
    std::println("Available XP: {}", _customer->getAvailableXP());
    std::println("1. Health Potion (30 XP)");
    std::println("2. Blade (50 XP)");
    std::println("3. Mirror (80 XP)");
    std::println("4. Ray (90 XP)");
    std::println("5. Shield (100 XP)");
    std::println("6. Back");
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 6);
    if (choice == 6) return;

    int cost = 0;
    if (choice == 1) cost = 30;
    else if (choice == 2) cost = 50;
    else if (choice == 3) cost = 80;
    else if (choice == 4) cost = 90;
    else if (choice == 5) cost = 100;

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
        std::println("Purchase of Item successful!");
    }
    else
    {
        std::println("Not enough XP!");
    }
}

void StoreManager::buyCharacter()
{
    std::println("\n--- Character Purchase ---");
    if (_customer->spendXP(50))
    {
        std::print("Successfully spent 50XP on new Character! ");
        _customer->addCharacter(createCharacterForSale());
        std::println("The Character is added to your profile!");
    }
    else
    {
        std::println("Not enough XP (Required - 50XP)!");
    }
}

std::unique_ptr<Character> StoreManager::createCharacterForSale()
{
    std::println("1. Warrior (20 HP, d8 dmg, Block)");
    std::println("2. Mage (12 HP, d12 dmg, Spell Magnification)");
    std::println("3. Archer (15 HP, d8 dmg, Poison Arrow)");
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 3);

    std::print("My character's name is: ");
    std::fflush(stdout);
    std::string charName = Input::getString();

    switch (choice)
    {
        case 1: return std::make_unique<Warrior>(charName);
        case 2: return std::make_unique<Mage>(charName);
        case 3: return std::make_unique<Archer>(charName);
        default: return std::make_unique<Warrior>(charName); // wont ever be reached, kept for comp. safety
    }
}

void StoreManager::levelUpCharacter()
{
    std::println("\n--- Levelling Up of Character ---");
    const auto& characters = _customer->getCharacters();
    
    if (characters.empty())
    {
        std::println("You don't have any Characters!");
        return;
    }

    std::println("Choose Character:");
    for (size_t i = 0; i < characters.size(); ++i)
    {
        std::println("{}. {} (Level {}, HP: {})",
            i + 1, characters[i]->getName(), characters[i]->getLevel(), characters[i]->getMaxHP());
    }
    
    std::print("I choose: ");
    std::fflush(stdout);

    int charChoice = Input::getInt(1, static_cast<int>(characters.size()));

    if (_customer->spendXP(100)) {
        std::println("\nChoose level up stat increase:");
        std::println("1. Increase max HP by 2");
        std::println("2. Increase max DMG by 1");
        std::print("I choose: ");
        std::fflush(stdout);

        int bonusChoice = Input::getInt(1, 2);
        Character* selectedChar = characters[charChoice - 1].get();
        
        if (bonusChoice == 1)
        {
            selectedChar->levelUpMaxHealth();
            std::println("{} now has {} maximum HP!", selectedChar->getName(), selectedChar->getMaxHP());
        }
        else if (bonusChoice == 2)
        {
            selectedChar->levelUpMaxDamage();
            std::println("{} now deals more DMG!", selectedChar->getName());
        }
    }
    else
    {
        std::println("Not enough XP (Required 100 XP)!");
    }
}