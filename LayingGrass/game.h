#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "player.h"
#include "tiles.h"

class Game {
private:
    Grid grid;
    std::vector<Player> players;

public:
    static void placeTile(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>>* boardGame, int x, int y);
    static void startGame(Grid myGrid, std::vector <Player> players, std::vector<std::vector<char>> startingTile);
};