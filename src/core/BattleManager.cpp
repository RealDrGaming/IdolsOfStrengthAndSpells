#include <print>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "BattleManager.h"
#include "../utils/Input.h"

User* BattleManager::findMatch(User* initiator, const std::vector<std::unique_ptr<User>>& allUsers)
{
    User* bestMatch = nullptr;
    int minDiff = std::numeric_limits<int>::max();

    for (const auto& user : allUsers)
    {
        if (user.get() == initiator) continue;

        int diff = std::abs(user->getBattlesWon() - initiator->getBattlesWon());
        if (diff < minDiff)
        {
            minDiff = diff;
            bestMatch = user.get();
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

    for (Character* h : {_hero1, _hero2})
    {
        h->fullRestore();
        h->setBladeActive(false);
        h->setMirrorActive(false);
        h->setShieldActive(false);
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
    bool turnCompleted = false;

    while (!turnCompleted)
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
            int dmg = attacker->calculateDamage();

            if (dmg > 0 && defender->hasShieldActive())
            {
                std::println(">>> {}'s Shield is active! All incoming damage is blocked!", defender->getName());
                dmg = 0;
                defender->setShieldActive(false);
            }
            else if (dmg > 0 && promptInterruptItem(defenderUser, "Shield"))
            {
                std::println(">>> {} used a Shield from inventory! All incoming damage is blocked!", defenderUser->getUsername());
                dmg = 0;
            }

            if (dmg > 0)
            {
                int block = defender->calculateDefense();
                dmg -= block;
                if (dmg < 0) dmg = 0;
            }

            std::println("\n>>> {} deals {} DMG to {}!", attacker->getName(), dmg, defender->getName());
            defender->takeDamage(dmg);
            std::println("{} has {} HP remaining.", defender->getName(), defender->getCurrentHP());

            turnCompleted = true;
        }
        else if (choice == 2)
        {
            turnCompleted = useItemTurn(attackerUser, attacker, defenderUser, defender);
        }
    }
}

bool BattleManager::useItemTurn(User* attackerUser, Character* attacker, User* defenderUser, Character* defender)
{
    const auto& items = attackerUser->getItems();

    std::vector<size_t> usableIndices;
    for (size_t i = 0; i < items.size(); ++i)
    {
        const std::string& name = items[i]->getName();
        if (name != "Shield" && name != "Ray") usableIndices.push_back(i);
    }

    if (usableIndices.empty())
    {
        if (items.empty())std::println("Your inventory is empty! Choose another action.");
        else std::println("You only have reactive items (Shield/Ray).");
        return false;
    }

    std::println("\n--- Inventory ---");
    for (size_t i = 0; i < usableIndices.size(); ++i)
    {
        std::println("{}. {}", i + 1, items[usableIndices[i]]->getName());
    }
    std::println("{}. Cancel", usableIndices.size() + 1);
    std::print("I choose: ");
    std::fflush(stdout);

    int choice = Input::getInt(1, static_cast<int>(usableIndices.size() + 1));

    if (choice == static_cast<int>(usableIndices.size() + 1))
        return false;

    size_t realItemIndex = usableIndices[choice - 1];
    Item* selectedItem = items[realItemIndex].get();
    selectedItem->use(attacker, defender);

    if (selectedItem->getName() == "Mirror")
    {
        if (promptInterruptItem(defenderUser, "Ray"))
        {
            std::println(">>> {} immediately used a Ray! The Mirror is shattered!", defenderUser->getUsername());
            defender->setMirrorActive(false);
        }
    }

    attackerUser->removeItem(realItemIndex);
    return true;
}

bool BattleManager::promptInterruptItem(User* defendingUser, const std::string& itemName)
{
    const auto& items = defendingUser->getItems();

    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i]->getName() == itemName)
        {
            std::print("\n[INTERRUPT] {}, you have a {}! Do you want to use it now? (y/n): ", defendingUser->getUsername(), itemName);
            std::fflush(stdout);

            if (Input::getYesNo())
            {
                defendingUser->removeItem(i);
                return true;
            }
            return false;
        }
    }
    return false;
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
    std::println("BATTLE ENDED! WINNER: {}!", winner->getUsername());
    std::println("=================================");

    winner->recordBattleResult(true);
    loser->recordBattleResult(false);

    winner->addXP(10);
    loser->addXP(5);
    
    std::println("{} receives 10 XP (Total: {})", winner->getUsername(), winner->getAvailableXP());
    std::println("{} receives 5 XP (Total: {})", loser->getUsername(), loser->getAvailableXP());

    winnerHero->fullRestore();
    loserHero->fullRestore();
}