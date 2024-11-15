#pragma once
#include <iostream>
#include <string>

class Player {
private:
    std::string name;
    std::string colorCode;
    std::string inventory;
public:
    Player(std::string name, int colorChoice);
    std::string getName();
    std::string getColorCode();

    static void displayColorOptions();
};