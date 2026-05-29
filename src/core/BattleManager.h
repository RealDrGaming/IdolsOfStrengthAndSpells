#pragma once

#include <vector>
#include <memory>

#include "../user/User.h"
#include "../characters/Character.h"

class BattleManager
{
private:
    User* _player1;
    User* _player2;
    Character* _hero1;
    Character* _hero2;

    Character* chooseHero(User* player);
    void playTurn(User* attackerUser, Character* attacker, User* defenderUser, Character* defender);
    void resolveBattle(User* winner, Character* winnerHero, User* loser, Character* loserHero);

    bool useItemTurn(User* attackerUser, Character* attacker, User* defenderUser, Character* defender);
    bool promptInterruptItem(User* defendingUser, const std::string& itemName);

public:
    static User* findMatch(User* initiator, const std::vector<std::unique_ptr<User>>& allUsers);

    BattleManager(User* p1, User* p2);
    
    void startBattle();
};