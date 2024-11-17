#include <iostream>
#include <string>
#include "grid.h"
#include "player.h"

void Grid::displayBoard(std::vector<Player> players) {
    std::cout << "   "; 
    for (size_t col = 0; col < boardGame->at(0).size(); ++col) {
        if (col < 10) std::cout << col << " ";
        else std::cout << col << " ";
    }
    std::cout << '\n';

    for (size_t row = 0; row < boardGame->size(); ++row) {
        int i = 0;
        if (row < 10) std::cout << row << "  ";
        else std::cout << row << " ";
        for (const auto& cell : boardGame->at(row)) {
            int isPlayedByPlayer = 0;
            for (auto& player : players) {
                if (player.hasCoordinate(row, i)) {
                    isPlayedByPlayer = 1;
                    if (cell == '.') {
                        if (i < 10) std::cout << cell << " ";
                        else std::cout << cell << "  ";
                    }
                    else {
                        if (i < 10) std::cout << player.getColorCode() << cell << "\033[0m" << " ";
                        else std::cout << player.getColorCode() << cell << "\033[0m" << "  ";
                    }
                }
            }
            if (isPlayedByPlayer == 0) {
                if (i < 10) std::cout << cell << " ";
                else std::cout << cell << "  ";
            }
            i++;
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<char>>* Grid::getBoard() {
    return boardGame;
}