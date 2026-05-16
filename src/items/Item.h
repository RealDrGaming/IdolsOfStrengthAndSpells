#pragma once

#include <string>

class Character;

class Item
{
protected:
    std::string _name;
    int _costXP;

public:
    Item(const std::string& name, int cost);

    virtual ~Item() = default;

    virtual void use(Character* myHero, Character* enemyHero) = 0;

    const std::string& getName() const;
    int getCostXP() const;
};