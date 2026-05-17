#include "GameManager.h"

#include <algorithm>
#include <iostream>

#include "../characters/Warrior.h"
#include "../characters/Mage.h"
#include "../characters/Archer.h"

#include "../items/HealingPotion.h"
#include "../items/Blade.h"
#include "../items/Mirror.h"
#include "../items/Ray.h"
#include "../items/Shield.h"

#include "StoreManager.h"

GameManager::GameManager() : _currentUser(nullptr) { }

GameManager& GameManager::getInstance()
{
    static GameManager instance;

    return instance;
}

void GameManager::run() {
    bool isRunning = true;

    while (isRunning)
    {
        if (_currentUser == nullptr) isRunning = showMainMenu();
        else showUserMenu();
    }
}

bool GameManager::showMainMenu()
{
    // --- guest menu ---

    std::cout << "\n=== Idols of Strength and Spells ===\n";
    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
    std::cout << "3. Leave\n";
    std::cout << "I choose: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) registerUser();
    else if (choice == 2) loginUser();
    else if (choice == 3) return false;

    return true;
}

void GameManager::showUserMenu()
{
    // --- logged user menu ---

    std::cout << "\nWelcome, " << _currentUser->getUsername() << "!\n";
    std::cout << "1. Battle\n";
    std::cout << "2. Store\n";
    std::cout << "3. Ranking\n";
    std::cout << "4. Logout\n";
    std::cout << "I choose: ";

    int choice;
    std::cin >> choice;

    if (choice == 1); //todo: implement battling
    else if (choice == 2)
    {
        StoreManager store(_currentUser);
        store.open();
    }
    else if (choice == 3); // todo: implement ranking system
    else if (choice == 4)
    {
        // logout
        _currentUser = nullptr;
    }
}

void GameManager::registerUser()
{
    std::string username, password;
    std::cout << "\n--- Register ---\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    auto newUser = std::make_unique<User>(username, password);

    std::cout << "\nChoose starting character! ( free )\n";
    newUser->addCharacter(chooseStartingCharacter());

    std::cout << "\nChoose a starting item! ( free )!\n";
    newUser->addItem(chooseStartingItem());

    _users.emplace_back(std::move(newUser));
    std::cout << "Registered! You can enter your profile now!.\n";
}

std::unique_ptr<Character> GameManager::chooseStartingCharacter()
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

std::unique_ptr<Item> GameManager::chooseStartingItem()
{
    int choice = 0;
    std::cout << "1. Healing Potion (Heals 5-10 HP) \n";
    std::cout << "2. Blade (Doubles next attack's dmg)\n";
    std::cout << "3. Mirror (Negates opponent's next special ability)\n";
    std::cout << "4. Ray (Negates the effect of Mirror)\n";
    std::cout << "5. Shield (Completely blocks opponent's next attack)\n";
    std::cout << "I choose item: ";
    std::cin >> choice;

    switch (choice) {
        case 1: return std::make_unique<HealingPotion>();
        case 2: return std::make_unique<Blade>();
        case 3: return std::make_unique<Mirror>();
        case 4: return std::make_unique<Ray>();
        case 5: return std::make_unique<Shield>();
        default:
            std::cout << "Invalid choice. Defaulting to Healing Potion.\n";
            return std::make_unique<HealingPotion>();
    }
}

void GameManager::loginUser()
{
    std::string inputUsername, inputPassword;

    std::cout << "\n--- Login ---\n";
    std::cout << "Username: ";
    std::cin >> inputUsername;
    std::cout << "Paswsord: ";
    std::cin >> inputPassword;

    auto it = std::find_if(_users.begin(), _users.end(),
        [&inputUsername, &inputPassword](const std::unique_ptr<User>& user)
        {
            return user->getUsername() == inputUsername && user->checkPassword(inputPassword);
        });

    if (it != _users.end())
    {
        _currentUser = it->get();

        std::cout << "Successful login! Welcome, " << _currentUser->getUsername() << "!\n";
    }
    else
    {
        std::cout << "Combination of username and password doesn't exist!\n";
    }
}