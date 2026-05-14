#pragma once
#include <string>

class Character
{
protected:
    std::string _name;
    int _maxHp;
    int _currHp;
    int _level;

public:
    Character(const std::string& name , int hp) : _name(name), _maxHp(hp), _currHp(hp), _level(1) { }

    virtual ~Character() = default;

    virtual void takeDamage(int amount) = 0;
    virtual int calculateDamage() = 0;

    virtual void triggerSpecialAbility() { }

    const std::string& getName() const { return _name; }
    int getCurrentHP() const { return _currHp; }
    int getMaxHP() const { return _maxHp; }
    bool isAlive() const { return _currHp > 0; }

    void heal(int amount) {
        _currHp += amount;
        if (_currHp > _maxHp) {
            _currHp = _maxHp;
        }
    }

    void fullRestore() {
        _currHp = _maxHp;
    }
};