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

void Game::askUserCoordinates(Grid myGrid, Player* player, std::vector<std::vector<char>> tile) {
    int x, y;
    std::cout << "Veuillez saisir les coordonnes x de votre prochaine tuile" << std::endl;
    std::cin >> x;
    std::cout << "Veuillez saisir les coordonnes y de votre prochaine tuile" << std::endl;
    std::cin >> y;
    std::cout << "Vous avez entre les coordonnes: ("<<x<<","<<y<<")\n";
    placeTile(tile, myGrid.getBoard(), x, y);
    for (size_t i = 0; i < tile.size(); i++) {
        for (size_t j = 0; j < tile[i].size(); j++) {
            player->addCoordinates(x+i, y+j);
        }
    }
}

std::string Game::getBiggestSquare(Grid myGrid, std::vector <Player> players) {
    std::vector<std::vector<char>>* grid = myGrid.getBoard();
    int squareSize = 0;
    std::string winingPlayer;
    Player player = players[0];
    for (int i = 0; i < grid->size(); i++) {
        for (int j = 0; j < (*grid)[i].size(); j++) {
            for (size_t playerIndex = 0; playerIndex < players.size(); playerIndex++) {
                if (players[playerIndex].hasCoordinate(i, j)) {
                    player = players[playerIndex];
                }
            }
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
                    if (ii - (i + 1) > squareSize) {
                        squareSize = ii - (i + 1);
                        winingPlayer = player.getName();
                    }
                }
            }
        }
    }
    std::cout << squareSize << std::endl;
    return winingPlayer;
}

void Game::rotateTileClockwise(std::vector<std::vector<char>>& tile) {
    // Vérification si la matrice est vide ou non carrée
    if (tile.empty() || tile[0].empty()) return;

    int rows = tile.size();
    int cols = tile[0].size();

    // Créer une nouvelle matrice pour la rotation
    std::vector<std::vector<char>> rotatedTile(cols, std::vector<char>(rows));

    // Remplir la nouvelle matrice en fonction de la rotation horaire
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotatedTile[j][rows - i - 1] = tile[i][j];
        }
    }

    // Copier la matrice rotée dans la matrice d'origine
    tile = rotatedTile;
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
            char response;
            do {
                std::cout << "Player: " << players[i].getName() << "turn\n";
                std::cout << "Take tile (T)\n";
                std::cout << "Exchange tile - " << players[i].nbCoupon() << " available (E)\n";
                std::cout << "Display queue (D)\n";
                std::cin >> response;
                if (response == 'd' || response == 'D') {
                    tiles.displayTileQueue(tileQueue);
                }
                else if (response == 'e' || response == 'E') {
                    tileQueue.pop();
                    players[i].removeCoupon();
                }
                else if (response == 't' || response == 'T') {
                    char tileResponse;
                    std::cout << "Tile to place\n";
                    auto tile = tileQueue.front();
                    tileQueue.pop();
                    do {
                        tiles.displayTile(tile);
                        std::cout << "Rotate tile (R)\n";
                        std::cout << "Place tile (P)\n";
                        std::cin >> tileResponse;
                        if (tileResponse == 'r' || tileResponse == 'R') {
                            Game::rotateTileClockwise(tile);
                        }
                        else if (tileResponse == 'p' || tileResponse == 'P') {
                            Game::askUserCoordinates(myGrid, &players[i], tile);
                            myGrid.displayBoard(players);
                        }
                    } while (tileResponse != 'p' && tileResponse != 'P');
                }
            } while (response != 't' && response != 'T');
        } 
    }
    std::string winner = Game::getBiggestSquare(myGrid, players);
    std::cout << "The winner is: " << winner << std::endl;
    return 0;
}