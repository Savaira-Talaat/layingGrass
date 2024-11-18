#pragma once
#include <iostream>
#include <string>
#include <vector>

class Player {
private:
    std::string name;
    std::string colorCode;
    int exchangeCoupon;
    std::vector<std::pair<int, int>> coordinates;

public:
    Player(std::string name, int colorChoice);
    std::string getName();
    std::string getColorCode();
    void addCoordinates(int x, int y);
    std::vector<std::pair<int, int>> getCoordinates();
    bool hasCoordinate(int x, int y) const;
    void displayColor();
    int nbCoupon();
    void addCoupon();
    void removeCoupon();
    static void displayColorOptions();
};