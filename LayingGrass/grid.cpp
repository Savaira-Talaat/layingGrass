#include <iostream>
#include <string>
#include "grid.h"
#include "player.h"

Grid::Grid(int s) : size(s) {
    int i;
    int j;
    boardGame = new int* [size];
    for (int i = 0; i < size; ++i) {
        boardGame[i] = new int[size];
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            boardGame[i][j] = 0;
            std::cout << boardGame[i][j] << " ";
        }
        std::cout << std::endl;
    }
};


Grid::~Grid() {
    delete[] boardGame;
};

void Grid::displayBoard() {
    int i;
    int j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            std::cout << boardGame[i][j] << std::endl;
        }
    }
};