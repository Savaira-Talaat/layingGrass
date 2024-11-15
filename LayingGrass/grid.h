#pragma once
#include <iostream>
#include <string>

class Grid {
private:
    int size;
    int** boardGame;
public:
    Grid(int s);
    ~Grid();
    void displayBoard();
};