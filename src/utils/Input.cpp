#include "Input.h"
#include <iostream>
#include <print>
#include <stdexcept>
#include <cstdio>

namespace Input
{
    std::string getString()
    {
        std::string input;

        while (true)
        {
            std::getline(std::cin, input);

            if (input.empty())
            {
                std::print("Input cannot be empty. Try again: ");
                std::fflush(stdout);
                continue;
            }
            if (input.find('|') != std::string::npos)
            {
                std::print("The character '|' is forbidden! Try again: ");
                std::fflush(stdout);
                continue;
            }
            return input;
        }
    }

    int getInt(int min, int max)
    {
        std::string input;
        int choice = 0;

        while (true)
        {
            std::getline(std::cin, input);

            try
            {
                size_t pos;
                choice = std::stoi(input, &pos);
                if (pos != input.size()) throw std::invalid_argument("trailing chars");

                if (choice >= min && choice <= max) return choice;
                
                std::print("Out of range [{}-{}]. Try again: ", min, max);
                std::fflush(stdout);
            }
            catch (const std::invalid_argument&)
            {
                std::print("Invalid input. Enter a number: ");
                std::fflush(stdout);
            }
            catch (const std::out_of_range&)
            {
                std::print("Number too large. Try again: ");
                std::fflush(stdout);
            }
        }
    }

    bool getYesNo()
    {
        std::string input;
        while (true)
        {
            std::getline(std::cin, input);
            if (input == "y" || input == "Y") return true;
            if (input == "n" || input == "N") return false;
            
            std::print("Invalid choice. Please enter 'y' or 'n': ");
            std::fflush(stdout);
        }
    }
}