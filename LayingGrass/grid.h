#pragma once
#include <iostream>
#include <string>
#include <vector>
class Grid {
private:
    int size;
    std::vector<std::vector<char>>* boardGame;
public:
    Grid(int s) : size(s) {
        boardGame = new std::vector<std::vector<char>>(size, std::vector<char>(size, '.'));
    }
    std::vector<std::vector<char>>* getBoard();
    void displayBoard();
};