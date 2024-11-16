#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "json.h"

class Player {
private:
    std::string name;
    std::string colorCode;
public:
    Player(std::string name, int colorChoice);
    std::string getName();
    std::string getColorCode();

    static void displayColorOptions();
};