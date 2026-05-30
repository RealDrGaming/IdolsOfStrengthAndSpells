#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../characters/Character.h"
#include "../items/Item.h"

class User {
private:
    std::string _username;
    std::string _password;
    
    int _totalXP;
    int _availableXP;
    
    int _battlesPlayed;
    int _battlesWon;

    std::vector<std::unique_ptr<Character>> _characters;
    std::vector<std::unique_ptr<Item>> _items;

public:
    User(const std::string& username, const std::string& password);

    const std::string& getUsername() const;
    int getTotalXP() const;
    int getAvailableXP() const;
    double getWinRate() const;
    int getBattlesWon() const;
    bool checkPassword(const std::string& inputPass) const;

    std::string getPassword() const;
    int getBattlesPlayed() const;
    void loadState(int totalXP, int availableXP, int battlesPlayed, int battlesWon);

    void addXP(int amount);
    bool spendXP(int amount);
    void recordBattleResult(bool won);

    void addCharacter(std::unique_ptr<Character> newCharacter);
    const std::vector<std::unique_ptr<Character>>& getCharacters() const;

    void addItem(std::unique_ptr<Item> newItem);
    const std::vector<std::unique_ptr<Item>>& getItems() const;
    void removeItem(size_t index);
};