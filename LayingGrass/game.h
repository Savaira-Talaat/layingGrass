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
    static void placeTile(const std::vector<std::vector<char>>& tile, std::vector<std::vector<char>>& board, int x, int y);
    static void startGame(Grid& myGrid, std::vector <Player>* players, std::vector<std::vector<char>> startingTile);
    static void askUserCoordinates(Grid& myGrid, Player* player, std::vector<Player>& players, std::vector<std::vector<char>> tile);
    static std::string getBiggestSquare(Grid myGrid, std::vector <Player> players);
    static void rotateTileClockwise(std::vector<std::vector<char>>& tile);
};