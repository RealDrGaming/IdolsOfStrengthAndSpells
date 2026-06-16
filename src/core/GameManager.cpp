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
#include "BattleManager.h"

#include "../utils/Input.h"
#include "../utils/Serializer.h"

GameManager::GameManager() : _currentUser(nullptr) { }

GameManager& GameManager::getInstance()
{
    static GameManager instance;

    return instance;
}

void GameManager::run() {
    bool isRunning = true;

    Serializer::loadGame(_users, "savegame.txt");

    while (isRunning)
    {
        if (_currentUser == nullptr) isRunning = showMainMenu();
        else showUserMenu();

        if (isRunning)
        {
            Serializer::saveGame(_users, "savegame.txt");
        }
    }

    Serializer::saveGame(_users, "savegame.txt");
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

    if (choice == 1)
    {
        User* opponent = BattleManager::findMatch(_currentUser, _users);

        if (opponent == nullptr)
        {
            std::println("Not enough registered users for battling!");
        }
        else
        {
            BattleManager battle(_currentUser, opponent);
            battle.startBattle();
        }
    }
    else if (choice == 2)
    {
        StoreManager store(_currentUser);
        store.open();
    }
    else if (choice == 3)
    {
        showLeaderboard();
    }
    else if (choice == 4)
    {
        // logout
        _currentUser = nullptr;
    }
}

void GameManager::registerUser()
{
    std::println("\n--- Register ---");

    std::string username;
    bool isUnique = false;

    while (!isUnique)
    {
        std::print("Username: ");
        std::fflush(stdout);
        username = Input::getString();

        auto it = std::find_if(_users.begin(), _users.end(),
            [&username](const std::unique_ptr<User>& u) { return u->getUsername() == username; });

        if (it != _users.end())
        {
            std::println("Error: The username '{}' is already taken! Please choose another.", username);
        }
        else
        {
            isUnique = true;
        }
    }

    std::print("Password: ");
    std::fflush(stdout);
    std::string password = Input::getString();

    auto newUser = std::make_unique<User>(username, password);

    std::println("\nChoose starting character! ( free )");
    newUser->addCharacter(chooseStartingCharacter());

    std::println("\nChoose a starting item! ( free )!");
    newUser->addItem(chooseStartingItem());

    _users.emplace_back(std::move(newUser));
    std::println("Registered! You can enter your profile now.");
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

    if (_users.empty())
    {
        std::println("No users are currently registered. Please register first.");
        return;
    }

    std::println("Select a user profile:");
    for (size_t i = 0; i < _users.size(); ++i)
    {
        std::println("{}. {}", i + 1, _users[i]->getUsername());
    }

    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, static_cast<int>(_users.size()));
    User* selectedUser = _users[choice - 1].get();

    std::print("Password for {}: ", selectedUser->getUsername());
    std::fflush(stdout);
    std::string inputPassword = Input::getString();

    if (selectedUser->checkPassword(inputPassword))
    {
        _currentUser = selectedUser;
        std::println("Successful login! Welcome, {}!", _currentUser->getUsername());
    }
    else
    {
        std::println("Error: Incorrect password!");
    }
}

void GameManager::showLeaderboard()
{
    std::println("\n=== Leaderboard ===");

    if (_users.empty())
    {
        std::println("There are no registered users!");
        return;
    }

    std::vector<User*> sortedUsers(_users.size());

    for (size_t i = 0; i < _users.size(); ++i)
    {
        sortedUsers[i] = _users[i].get();
    }

    std::ranges::sort(sortedUsers, [](User* a, User* b)
    {
        if (a->getBattlesWon() != b->getBattlesWon())
            return a->getBattlesWon() > b->getBattlesWon();

        if (a->getTotalXP() != b->getTotalXP())
            return a->getTotalXP() > b->getTotalXP();

        return a->getWinRate() > b->getWinRate();
    });

    for (size_t i = 0; i < sortedUsers.size(); ++i)
    {
        User* u = sortedUsers[i];
        std::println("{}. {} | Wins: {} | Total XP: {} | Win Rate: {:.2f}%",
                     i + 1, u->getUsername(), u->getBattlesWon(), u->getTotalXP(), u->getWinRate());
    }
}