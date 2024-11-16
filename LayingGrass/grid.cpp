#include <iostream>
#include <string>
#include "grid.h"
#include "player.h"

void Grid::displayBoard() {
    int i;
    int j;
    for (const auto& row : *boardGame) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
};

std::vector<std::vector<char>>* Grid::getBoard() {
    return boardGame;
}