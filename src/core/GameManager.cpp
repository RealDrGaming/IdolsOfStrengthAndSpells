#include "GameManager.h"

#include <algorithm>
#include <print>
#include <string>
#include <cstdio>

#include "../characters/Warrior.h"
#include "../characters/Mage.h"
#include "../characters/Archer.h"

#include "../items/HealingPotion.h"
#include "../items/Blade.h"
#include "../items/Mirror.h"
#include "../items/Ray.h"
#include "../items/Shield.h"

#include "StoreManager.h"

#include "../utils/Input.h"

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

    std::println("\n=== Idols of Strength and Spells ===");
    std::println("1. Register");
    std::println("2. Login");
    std::println("3. Leave");
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 3);

    if (choice == 1) registerUser();
    else if (choice == 2) loginUser();
    else if (choice == 3) return false;

    return true;
}

void GameManager::showUserMenu()
{
    // --- logged user menu ---

    std::println("\nWelcome, {}!", _currentUser->getUsername());
    std::println("1. Battle");
    std::println("2. Store");
    std::println("3. Ranking");
    std::println("4. Logout");
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 4);

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
    std::println("\n--- Register ---");
    std::print("Username: ");
    std::fflush(stdout);
    std::string username = Input::getString();

    std::print("Password: ");
    std::fflush(stdout);
    std::string password = Input::getString();

    auto newUser = std::make_unique<User>(username, password);

    std::println("\nChoose starting character! ( free )");
    newUser->addCharacter(chooseStartingCharacter());

    std::println("\nChoose a starting item! ( free )!");
    newUser->addItem(chooseStartingItem());

    _users.emplace_back(std::move(newUser));
    std::println("Registered! You can enter your profile now!.");
}

std::unique_ptr<Character> GameManager::chooseStartingCharacter()
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

std::unique_ptr<Item> GameManager::chooseStartingItem()
{
    std::println("1. Healing Potion (Heals 5-10 HP)");
    std::println("2. Blade (Doubles next attack's dmg)");
    std::println("3. Mirror (Negates opponent's next special ability)");
    std::println("4. Ray (Negates the effect of Mirror)");
    std::println("5. Shield (Completely blocks opponent's next attack)");
    std::print("I choose item: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 5);

    switch (choice)
    {
        case 1: return std::make_unique<HealingPotion>();
        case 2: return std::make_unique<Blade>();
        case 3: return std::make_unique<Mirror>();
        case 4: return std::make_unique<Ray>();
        case 5: return std::make_unique<Shield>();
        default: return std::make_unique<HealingPotion>(); // wont ever be reached, kept for comp. safety
    }
}

void GameManager::loginUser()
{
    std::println("\n--- Login ---");
    std::print("Username: ");
    std::fflush(stdout);
    std::string inputUsername = Input::getString();

    std::print("Password: ");
    std::fflush(stdout);
    std::string inputPassword = Input::getString();

    auto it = std::find_if(_users.begin(), _users.end(),
        [&inputUsername, &inputPassword](const std::unique_ptr<User>& user)
        {
            return user->getUsername() == inputUsername && user->checkPassword(inputPassword);
        });

    if (it != _users.end())
    {
        _currentUser = it->get();
        std::println("Successful login! Welcome, {}!", _currentUser->getUsername());
    }
    else
    {
        std::println("Combination of username and password doesn't exist!");
    }
}