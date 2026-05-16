#include "User.h"

User::User(const std::string& username, const std::string& password)
    : _username(username), _password(password), _totalXP(0), _availableXP(0), _battlesPlayed(0), _battlesWon(0) { }

const std::string& User::getUsername() const
{
    return _username;
}

int User::getTotalXP() const
{
    return _totalXP;
}

int User::getAvailableXP() const
{
    return _availableXP;
}

double User::getWinRate() const
{
    if (_battlesPlayed == 0) return 0.0;

    return (static_cast<double>(_battlesWon) / _battlesPlayed) * 100.0;
}

bool User::checkPassword(const std::string& inputPass) const
{
    return _password == inputPass;
}

void User::addXP(int amount)
{
    _totalXP += amount;
    _availableXP += amount;
}

bool User::spendXP(int amount)
{
    if (_availableXP >= amount)
    {
        _availableXP -= amount;
        return true;
    }

    return false;
}

void User::recordBattleResult(bool won)
{
    _battlesPlayed++;

    if (won) _battlesWon++;
}

void User::addCharacter(std::unique_ptr<Character> newCharacter)
{
    newCharacter->setOwner(this->getUsername());

    _characters.emplace_back(std::move(newCharacter));
}

const std::vector<std::unique_ptr<Character>>& User::getCharacters() const
{
    return _characters;
}

void User::addItem(std::unique_ptr<Item> newItem)
{
    _items.emplace_back(std::move(newItem));
}

const std::vector<std::unique_ptr<Item>>& User::getItems() const
{
    return _items;
}

void User::removeItem(size_t index)
{
    if (index < _items.size())
        _items.erase(_items.begin() + index);
}