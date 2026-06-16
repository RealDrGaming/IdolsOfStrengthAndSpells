#include "Serializer.h"

#include <fstream>
#include <sstream>
#include <print>

#include "../characters/Warrior.h"
#include "../characters/Mage.h"
#include "../characters/Archer.h"

#include "../items/HealingPotion.h"
#include "../items/Blade.h"
#include "../items/Mirror.h"
#include "../items/Ray.h"
#include "../items/Shield.h"

void Serializer::saveGame(const std::vector<std::unique_ptr<User>>& users, const std::string& filepath)
{
    std::ofstream file(filepath);

    if (!file.is_open())
    {
        std::println("Error: Failed to open save file for writing!");
        return;
    }

    for (const auto& user : users)
    {
        file << "USER|" << user->getUsername() << "|" << user->getPassword() << "|"
             << user->getTotalXP() << "|" << user->getAvailableXP() << "|"
             << user->getBattlesPlayed() << "|" << user->getBattlesWon() << "\n";

        for (const auto& hero : user->getCharacters())
        {
            std::string type = "Warrior";
            if (dynamic_cast<Mage*>(hero.get())) type = "Mage";
            else if (dynamic_cast<Archer*>(hero.get())) type = "Archer";

            file << "CHARACTER|" << type << "|" << hero->getName() << "|"
                 << hero->getCurrentHP() << "|" << hero->getMaxHP() << "|"
                 << hero->getLevel() << "|" << hero->getMaxDamage() << "\n";
        }

        for (const auto& item : user->getItems())
        {
            file << "ITEM|" << item->getName() << "\n";
        }

        file << "END_USER\n";
    }

    file.close();
}

void Serializer::loadGame(std::vector<std::unique_ptr<User>>& users, const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) return;

    users.clear();
    std::string line;
    User* currentUser = nullptr;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        try
        {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, '|'))
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "USER" && tokens.size() >= 7)
            {
                auto newUser = std::make_unique<User>(tokens[1], tokens[2]);
                newUser->loadState(std::stoi(tokens[3]), std::stoi(tokens[4]),
                                   std::stoi(tokens[5]), std::stoi(tokens[6]));
                users.push_back(std::move(newUser));
                currentUser = users.back().get();
            }
            else if (tokens[0] == "CHARACTER" && tokens.size() >= 7 && currentUser)
            {
                std::unique_ptr<Character> hero;
                if (tokens[1] == "Warrior") hero = std::make_unique<Warrior>(tokens[2]);
                else if (tokens[1] == "Mage")    hero = std::make_unique<Mage>(tokens[2]);
                else if (tokens[1] == "Archer")  hero = std::make_unique<Archer>(tokens[2]);

                if (hero)
                {
                    hero->loadState(std::stoi(tokens[3]), std::stoi(tokens[4]),
                                    std::stoi(tokens[5]), std::stoi(tokens[6]));
                    currentUser->addCharacter(std::move(hero));
                }
            }
            else if (tokens[0] == "ITEM" && tokens.size() >= 2 && currentUser)
            {
                std::unique_ptr<Item> item;
                if      (tokens[1] == "Healing Potion") item = std::make_unique<HealingPotion>();
                else if (tokens[1] == "Blade")          item = std::make_unique<Blade>();
                else if (tokens[1] == "Mirror")         item = std::make_unique<Mirror>();
                else if (tokens[1] == "Ray")            item = std::make_unique<Ray>();
                else if (tokens[1] == "Shield")         item = std::make_unique<Shield>();

                if (item) currentUser->addItem(std::move(item));
            }
            else if (tokens[0] == "END_USER")
            {
                currentUser = nullptr;
            }
        }
        catch (const std::exception& e)
        {
            std::println("Warning: Skipping corrupted save line: {}", line);
        }
    }
}