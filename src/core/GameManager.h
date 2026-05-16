#pragma once

#include <vector>
#include <memory>
#include "../user/User.h"

class GameManager {
private:
    std::vector<std::unique_ptr<User>> _users;

    // wont cause memory leaks bcuz it doesnt allocate memory
    User* _currentUser;

    void showMainMenu();
    void registerUser();
    void loginUser();

    std::unique_ptr<Character> chooseStartingCharacter();

public:
    GameManager();
    void run();
};