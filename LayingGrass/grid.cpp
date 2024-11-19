#include <iostream>
#include <string>
#include "grid.h"
#include "player.h"
#include <algorithm>
#include <random> 

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

std::vector<std::vector<char>>& Grid::getBoard() {
    return *boardGame;
}

void Grid::distributeBonuses(int nbPlayers) {
    int rows = boardGame->size();
    int cols = (*boardGame)[0].size();

    int tileExchangeCount = std::ceil(1.5 * nbPlayers);
    int stoneCount = std::ceil(0.5 * nbPlayers);
    int robberyCount = nbPlayers;

    std::vector<char> bonuses(tileExchangeCount, 'E');
    bonuses.insert(bonuses.end(), stoneCount, 'S');
    bonuses.insert(bonuses.end(), robberyCount, 'R');
    std::shuffle(bonuses.begin(), bonuses.end(), std::mt19937{ std::random_device{}() });
    while (!bonuses.empty()) {
        int x = rand() % (rows - 2) + 1;
        int y = rand() % (cols - 2) + 1;
        if ((*boardGame)[x][y] == '.' &&
            (*boardGame)[x - 1][y] != 'E' && (*boardGame)[x - 1][y] != 'S' && (*boardGame)[x - 1][y] != 'R' &&
            (*boardGame)[x + 1][y] != 'E' && (*boardGame)[x + 1][y] != 'S' && (*boardGame)[x + 1][y] != 'R' &&
            (*boardGame)[x][y - 1] != 'E' && (*boardGame)[x][y - 1] != 'S' && (*boardGame)[x][y - 1] != 'R' &&
            (*boardGame)[x][y + 1] != 'E' && (*boardGame)[x][y + 1] != 'S' && (*boardGame)[x][y + 1] != 'R') {

            (*boardGame)[x][y] = bonuses.back();
            bonuses.pop_back();
        }
    }
}
