#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "player.h"

class Game {
private:
	Grid grid;
	std::vector<Player> players;

public:
	Game(int nbPlayer);

};
