#pragma once
#include <iostream>
#include <string>
#include "player.cpp"

class Player {
private:
    std::string name;
    std::string color;
public:
    Player(std::string name, std::string color);
    std::string getName();
};