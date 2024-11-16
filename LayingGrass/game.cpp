#include <iostream>
#include <string>
#include "game.h"
#include "tiles.h"

void Game::placeTile(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>>* boardGame, int x, int y) {
    for (int i = x, iS = 0; i < x + 5 && iS < 5; i++, iS++) {
        for (int j = y, jS = 0; j < y + 3 && jS < 3; j++, jS++) {
            if (iS < tiles.size() && jS < tiles[iS].size() && tiles[iS][jS] == '#') {
                (*boardGame)[i][j] = tiles[iS][jS];
                std::cout << (*boardGame)[i][j] << "\n";
                std::cout << "test" << "\n";
            }
        }
    }
}

void Game::startGame(Grid myGrid,std::vector <Player> players, std::vector<std::vector<char>> startingTile) {
    for (size_t i = 0; i < players.size(); i++) {
        int x = 0;
        int y = 0;
        std::cout << "Veuillez saisir les coordonnées x de votre tuile de depart" << std::endl;
        std::cin >> x;
        std::cout << "Veuillez saisir les coordonnées y de votre tuile de depart" << std::endl;
        std::cin >> y;
        placeTile(startingTile, myGrid.getBoard(), x, y);
        myGrid.displayBoard();
    }
};


int main()
{
    std::string name;
    int colorChoice;
    int nbPlayer = 0;
    std::vector<Player> players;
    Tiles tiles;
    auto& startingTile = tiles.getStartingTile("tuiles.json");  // Obtient la première ligne des tuiles

    do {
        std::cout << "How many players are you?" << std::endl;
        std::cin >> nbPlayer;
    } while (nbPlayer > 9 || nbPlayer < 2);

    for (int i = 1; i <= nbPlayer; i++) {
        std::cout << "What's your name" << std::endl;
        std::cin >> name;


        Player::displayColorOptions();
        std::cin >> colorChoice;

        Player p1(name, colorChoice);
        players.push_back(p1);

        std::cout << p1.getColorCode() << "Player: " << p1.getName() << "\033[0m" << std::endl;
    };

    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << "Player : " << players[i].getColorCode() << players[i].getName() << "\033[0m" << std::endl;
    }
    int s = 30;
    if (nbPlayer >= 2 && nbPlayer <= 4) {
        s = 20;
    }
    Grid myGrid(s);
    myGrid.displayBoard();
    Game::startGame(myGrid, players, startingTile);
    return 0;
}