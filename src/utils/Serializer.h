#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../user/User.h"

class Serializer
{
public:
    static void saveGame(const std::vector<std::unique_ptr<User>>& users, const std::string& filepath);
    static void loadGame(std::vector<std::unique_ptr<User>>& users, const std::string& filepath);
};