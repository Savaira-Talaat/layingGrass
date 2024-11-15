#include <iostream>
#include <string>
#include "player.h"

int textColor;
int nblayer = 0;
Player::Player(std::string name, std::string color) {
    this->name = name;
    this->color = color;
};

std::string Player::getName() {
    return name;
};

int main()
{
    std::string name;
    std::cout << "What's your name" << std::endl;
    std::cin >> name;
    Player p1(name, "grey");
    std::string a = "■■■■";
    std::cout << a;
}