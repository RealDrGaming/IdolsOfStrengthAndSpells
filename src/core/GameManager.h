#pragma once

#include <vector>
#include <memory>
#include "../user/User.h"

class GameManager {
private:
    // wont cause memory leaks bcuz it doesnt allocate memory
    User* _currentUser;
    std::vector<std::unique_ptr<User>> _users;

    bool showMainMenu();
    void showUserMenu();

    GameManager();

    void registerUser();
    void loginUser();

    std::unique_ptr<Character> chooseStartingCharacter();
    std::unique_ptr<Item> chooseStartingItem();

public:
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    static GameManager& getInstance();

    void run();
};