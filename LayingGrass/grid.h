#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "player.h"

class Grid {
private:
    int size;
    std::vector<std::vector<char>>* boardGame;
public:
    Grid(int s) : size(s) {
        boardGame = new std::vector<std::vector<char>>(size, std::vector<char>(size, '.'));
    }
    ~Grid() {
        delete boardGame;
    }
    std::vector<std::vector<char>>& getBoard();
    void displayBoard(std::vector<Player> players);
    void distributeBonuses(int nbPlayers);
};