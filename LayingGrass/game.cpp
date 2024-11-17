#include <iostream>
#include <string>
#include "game.h"
#include "tiles.h"


void Game::placeTile(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>>* boardGame, int x, int y) {
    for (int i = x, iS = 0; i < x + 5 && iS < 5; i++, iS++) {
        for (int j = y, jS = 0; j < y + 3 && jS < 3; j++, jS++) {
            if (iS < tiles.size() && jS < tiles[iS].size() && tiles[iS][jS] == '#') {
                (*boardGame)[i][j] = tiles[iS][jS];
            }
        }
    }
}

void Game::startGame(Grid myGrid,std::vector <Player>* players, std::vector<std::vector<char>> startingTile) {
    for (size_t i = 0; i < players->size(); i++) {
        int x = 0;
        int y = 0;
        std::cout << "Veuillez saisir les coordonnees x de votre tuile de depart" << std::endl;
        std::cin >> x;
        std::cout << "Veuillez saisir les coordonnees y de votre tuile de depart" << std::endl;
        std::cin >> y;
        placeTile(startingTile, myGrid.getBoard(), x, y);
        (*players)[i].addCoordinates(x, y);
        myGrid.displayBoard(*players);
    }
};

void Game::askUserCoordinates(Grid myGrid, Player* player, std::queue<std::vector<std::vector<char>>>* tileQueue) {
    int x, y;
    std::cout << "Veuillez saisir les coordonnes x de votre prochaine tuile" << std::endl;
    std::cin >> x;
    std::cout << "Veuillez saisir les coordonnes y de votre prochaine tuile" << std::endl;
    std::cin >> y;

    auto tileToPlace = tileQueue->front();
    placeTile(tileToPlace, myGrid.getBoard(), x, y);
    for (size_t i = 0; i < tileToPlace.size(); i++) {
        for (size_t j = 0; j < tileToPlace[i].size(); j++) {
            player->addCoordinates(x+i, y+j);
        }
    }
    tileQueue->pop();
}

int Game::getBiggestSquare(Grid myGrid) {
    std::vector<std::vector<char>>* grid = myGrid.getBoard();
    int squareSize = 0;
    for (int i = 0; i < grid->size(); i++) {
        for (int j = 0; j < (*grid)[i].size(); j++) {
            if ((*grid)[i][j] == '#') {
                int isSquare = 1;
                int ii = i + 1;
                int jj = j + 1;
                while (isSquare == 1) {
                    for (int iii = i + 1; iii <= ii; iii++) {
                        for (int jjj = j + 1; jjj <= jj; jjj++) {
                            if ((*grid)[iii][jjj] == '.') {
                                isSquare = 0;
                            }
                        }
                    }
                    ii++;
                    jj++;
                    if (ii - i > squareSize) {
                        squareSize = ii - (i + 1);
                    }
                }
            }
        }
    }
    return squareSize;
}


int main()
{
    std::string name;
    int colorChoice;
    int nbPlayer = 0;
    std::vector<Player> players;
    Tiles tiles;
    auto& startingTile = tiles.getStartingTile("tuiles.json");
    std::queue<std::vector<std::vector<char>>> tileQueue = tiles.iniatializeQueue("tuiles.json");
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
    myGrid.displayBoard(players);
    Game::startGame(myGrid, &players, startingTile);
    int totalTurn = 1 * nbPlayer;
    for (int turn = 1; turn <= 3; turn++) {
        std::cout << "turn number: " << turn << std::endl;
        for (size_t i = 0; i < players.size(); ++i) {
            tiles.displayTileQueue(tileQueue);
            Game::askUserCoordinates(myGrid, &players[i], &tileQueue);
            myGrid.displayBoard(players);
        }
    }
    int biggestSquare = Game::getBiggestSquare(myGrid);
    std::cout << "The biggest square is: " << biggestSquare << std::endl;
    return 0;
}