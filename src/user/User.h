#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../characters/Character.h"

class User {
private:
    std::string _username;
    std::string _password;
    
    int _totalXP;
    int _availableXP;
    
    int _battlesPlayed;
    int _battlesWon;

    std::vector<std::unique_ptr<Character>> _characters;

public:
    User(const std::string& username, const std::string& password);

    const std::string& getUsername() const;
    int getTotalXP() const;
    int getAvailableXP() const;
    double getWinRate() const;

    void addXP(int amount);
    bool spendXP(int amount);
    void recordBattleResult(bool won);

    void addCharacter(std::unique_ptr<Character> newCharacter);
    const std::vector<std::unique_ptr<Character>>& getCharacters() const;
};