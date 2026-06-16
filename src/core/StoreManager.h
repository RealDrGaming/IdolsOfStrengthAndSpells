#pragma once

#include <memory>
#include "../user/User.h"
#include "../characters/Character.h"

class StoreManager
{
private:
    User* _customer;

    void buyItem();
    void buyCharacter();
    void levelUpCharacter();

public:
    StoreManager(User* customer);

    void open();
};