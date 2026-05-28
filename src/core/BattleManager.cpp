#include <print>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "BattleManager.h"
#include "../utils/Input.h"

User* BattleManager::findMatch(User* initiator, const std::vector<std::unique_ptr<User>>& allUsers)
{
    User* bestMatch = nullptr;
    int minDiff = std::numeric_limits<int>::max();

    for (const auto& u : allUsers)
    {
        if (u.get() == initiator) continue;

        int diff = std::abs(u->getBattlesWon() - initiator->getBattlesWon());
        if (diff < minDiff)
        {
            minDiff = diff;
            bestMatch = u.get();
        }
    }

    return bestMatch;
}

BattleManager::BattleManager(User* p1, User* p2) : _player1(p1), _player2(p2), _hero1(nullptr), _hero2(nullptr) { }

void BattleManager::startBattle()
{
    std::println("\n=== MATCHMAKING SUCCESS ===");
    std::println("{} VS {}", _player1->getUsername(), _player2->getUsername());

    _hero1 = chooseHero(_player1);
    _hero2 = chooseHero(_player2);

    if (!_hero1 || !_hero2)
    {
        std::println("One of the users does not have a valid character!");
        return;
    }

    bool isPlayer1Turn = (std::rand() % 2 == 0);
    std::println("\n{} starts first!", isPlayer1Turn ? _player1->getUsername() : _player2->getUsername());

    bool battleOver = false;
    while (!battleOver)
    {
        if (isPlayer1Turn)
        {
            playTurn(_player1, _hero1, _player2, _hero2);
            if (_hero2->getCurrentHP() <= 0) 
            {
                resolveBattle(_player1, _hero1, _player2, _hero2);
                battleOver = true;
            }
        }
        else
        {
            playTurn(_player2, _hero2, _player1, _hero1);
            if (_hero1->getCurrentHP() <= 0) 
            {
                resolveBattle(_player2, _hero2, _player1, _hero1);
                battleOver = true;
            }
        }

        isPlayer1Turn = !isPlayer1Turn; 
    }
}

void BattleManager::playTurn(User* attackerUser, Character* attacker, User* defenderUser, Character* defender)
{
    std::println("\n--- {}'s turn! (Character: {}, HP: {}) ---",
        attackerUser->getUsername(), attacker->getName(), attacker->getCurrentHP());
    
    std::println("1. Attack");
    std::println("2. Use Item");
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, 2);

    if (choice == 1)
    {
        // TODO: Mirror check

        int dmg = attacker->calculateDamage();

        // TODO: Blade check

        // TODO: Prompt interruption

        // TODO: Warrior defense check

        std::println("\n>>> {} deals {} DMG to {}!", attacker->getName(), dmg, defender->getName());
        defender->takeDamage(dmg);
        std::println("{} has {} HP remaining.", defender->getName(), defender->getCurrentHP());
    }
    else
    {
        std::println("Items not implemented yet!");
    }
}

Character* BattleManager::chooseHero(User* player)
{
    std::println("\n{}! Choose character to fight with:", player->getUsername());
    const auto& heroes = player->getCharacters();

    if (heroes.empty()) return nullptr;

    for (size_t i = 0; i < heroes.size(); ++i)
    {
        std::println("{}. {} (HP: {}/{})", 
            i + 1, heroes[i]->getName(), heroes[i]->getCurrentHP(), heroes[i]->getMaxHP());
    }
    
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, static_cast<int>(heroes.size()));
    return heroes[choice - 1].get();
}

void BattleManager::resolveBattle(User* winner, Character* winnerHero, User* loser, Character* loserHero)
{
    std::println("\n=================================");
    std::println("BATTLE ENDED! WINNNER: {}!", winner->getUsername());
    std::println("=================================");

    winner->recordBattleResult(true);
    loser->recordBattleResult(false);

    winner->addXP(10);
    loser->addXP(5);
    
    std::println("{} receives 10 XP (Total: {})", winner->getUsername(), winner->getAvailableXP());
    std::println("{} receives 5 XP (Total: {})", loser->getUsername(), loser->getAvailableXP());

    winnerHero->heal(winnerHero->getMaxHP());
    loserHero->heal(loserHero->getMaxHP());
}