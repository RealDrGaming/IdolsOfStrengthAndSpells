#include "Character.h"

Character::Character(const std::string& name, int hp, int maxDamage)
    : _name(name), _maxHp(hp), _currHp(hp), _level(1), _maxDamage(maxDamage), _ownerUsername("") { }

void Character::triggerSpecialAbility() { }

const std::string& Character::getName() const { return _name; }
int Character::getCurrentHP() const { return _currHp; }
int Character::getMaxHP() const { return _maxHp; }
int Character::getLevel() const { return _level; }
const std::string& Character::getOwner() const { return _ownerUsername; }

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

void Character::setOwner(const std::string& ownerName)
{
    _ownerUsername = ownerName;
}

void Character::levelUpMaxHealth()
{
    _level++;
    _maxHp += 2;
}

void Character::levelUpMaxDamage()
{
    _level++;
    _maxDamage += 1;
}