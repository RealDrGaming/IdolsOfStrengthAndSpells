#include "Item.h"

Item::Item(const std::string& name, int cost) : _name(name), _costXP(cost) { }

const std::string& Item::getName() const
{
    return _name;
}

int Item::getCostXP() const
{
    return _costXP;
}