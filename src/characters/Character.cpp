#include "Character.h"

Character::Character(const std::string& name, int hp, int maxDamage)
    : _name(name), _maxHp(hp), _currHp(hp), _level(1), _maxDamage(maxDamage), _ownerUsername(""),
        _hasBladeActive(false), _hasMirrorActive(false), _hasShieldActive(false) { }

void Character::takeDamage(int amount)
{
    _currHp -= amount;

    if (_currHp < 0) _currHp = 0;
}

int Character::calculateDefense()
{
    return 0;
}

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

int Character::getMaxDamage() const { return _maxDamage; }

void Character::loadState(int currHp, int maxHp, int level, int maxDamage)
{
    _currHp = currHp;
    _maxHp = maxHp;
    _level = level;
    _maxDamage = maxDamage;
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

bool Character::hasBladeActive() const { return _hasBladeActive; }
void Character::setBladeActive(bool isBladeActive) { _hasBladeActive = isBladeActive; }

bool Character::hasMirrorActive() const { return _hasMirrorActive; }
void Character::setMirrorActive(bool isMirrorActive) { _hasMirrorActive = isMirrorActive; }

bool Character::hasShieldActive() const { return _hasShieldActive; }
void Character::setShieldActive(bool isShieldActive) { _hasShieldActive = isShieldActive; }