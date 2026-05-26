#pragma once
#include <string>

namespace Input
{
    std::string getString();
    int getInt(int min, int max);
    bool getYesNo();
}