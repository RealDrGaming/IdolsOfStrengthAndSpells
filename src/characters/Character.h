#pragma once

#include <string>

class Character
{
protected:
    std::string _name;
    int _maxHp;
    int _currHp;
    int _level;

    int _maxDamage;
    std::string _ownerUsername;

public:
    Character(const std::string& name , int hp, int maxDamage);

    virtual ~Character() = default;

    virtual void takeDamage(int amount) = 0;
    virtual int calculateDamage() = 0;

    virtual void triggerSpecialAbility();

    const std::string& getName() const;
    int getCurrentHP() const;
    int getMaxHP() const;
    int getLevel() const;
    const std::string& getOwner() const;
    bool isAlive() const;

    void heal(int amount);
    void fullRestore();

    void setOwner(const std::string& ownerName);

    void levelUpMaxHealth();
    void levelUpMaxDamage();
};