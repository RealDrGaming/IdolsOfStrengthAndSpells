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

    bool _hasBladeActive;
    bool _hasMirrorActive;
    bool _hasShieldActive;

public:
    Character(const std::string& name , int hp, int maxDamage);

    virtual ~Character() = default;

    void takeDamage(int amount);

    virtual int calculateDamage() = 0;
    virtual int calculateDefense();

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

    bool hasBladeActive() const;
    void setBladeActive(bool state);

    bool hasMirrorActive() const;
    void setMirrorActive(bool state);

    bool hasShieldActive() const;
    void setShieldActive(bool state);
};