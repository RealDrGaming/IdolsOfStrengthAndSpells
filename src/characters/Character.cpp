#include "Character.h"

Character::Character(const std::string& name, int hp) : _name(name), _maxHp(hp), _currHp(hp), _level(1) { }

void Character::triggerSpecialAbility() { }

const std::string& Character::getName() const
{
    return _name;
}

int Character::getCurrentHP() const
{
    return _currHp;
}

int Character::getMaxHP() const
{
    return _maxHp;
}

bool Character::isAlive() const
{
    return _currHp > 0;
}

void Character::heal(int amount)
{
    _currHp += amount;

    if (_currHp > _maxHp) _currHp = _maxHp;
}

void Character::fullRestore()
{
    _currHp = _maxHp;
}