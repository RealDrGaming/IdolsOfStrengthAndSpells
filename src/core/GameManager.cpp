#include "GameManager.h"

#include <algorithm>
#include <iostream>
#include "../characters/Warrior.h"
#include "../characters/Mage.h"
#include "../characters/Archer.h"

GameManager::GameManager() : _currentUser(nullptr) { }

void GameManager::run()
{
    bool isRunning = true;
    while (isRunning)
    {
        if (_currentUser == nullptr)
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
            else if (choice == 3) isRunning = false;
        }
        else
        {
            // --- logged user menu ---

            std::cout << "\nWelcome, " << _currentUser->getUsername() << "!\n";
            std::cout << "1. Leave\n";

            int choice;
            std::cin >> choice;

            // logout
            if (choice == 1) _currentUser = nullptr;
        }
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

    _users.push_back(std::move(newUser));
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