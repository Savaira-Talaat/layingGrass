#include <iostream>
#include <string>
#include "game.h"
#include "tiles.h"


void Game::placeTile(const std::vector<std::vector<char>>& tiles, std::vector<std::vector<char>>& boardGame, int x, int y) {
    for (int i = x, iS = 0; i < x + tiles.size() && iS < 5; i++, iS++) {
        for (int j = y, jS = 0; j < y + tiles[0].size() && jS < 3; j++, jS++) {
            if (iS < tiles.size() && jS < tiles[iS].size() && tiles[iS][jS] == '#') {
                boardGame[i][j] = '#';
            }
        }
    }
}

void Game::startGame(Grid& myGrid,std::vector <Player>* players, std::vector<std::vector<char>> startingTile) {
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

void checkAndApplyBonus(Player* player, std::vector<Player>& players, std::vector<std::vector<char>>& board, int x, int y) {
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
            char bonus = board[nx][ny];

            if (bonus == 'E') {
                player->addCoupon();
                board[nx][ny] = '.';
            }
            else if (bonus == 'S') {
                player->placeStone(board);
                board[nx][ny] = '.';
            }
            else if (bonus == 'R') {
                player->stealCouponFromOtherPlayer(players);
                board[nx][ny] = '.';
            }
        }
    }
}


void Game::askUserCoordinates(Grid& myGrid, Player* player, std::vector<Player>& players, std::vector<std::vector<char>> tile) {
    int x, y;
    std::cout << "Veuillez saisir les coordonnees x de votre prochaine tuile" << std::endl;
    std::cin >> x;
    std::cout << "Veuillez saisir les coordonnees y de votre prochaine tuile" << std::endl;
    std::cin >> y;
    std::cout << "Vous avez saisi les coordonnees: (" << x << "," << y << ")\n";

    std::cout << "Appel de la fonction placeTile\n";
    placeTile(tile, myGrid.getBoard(), x, y);

    std::cout << "Apres la fonction placeTile\n";
    for (size_t i = 0; i < tile.size(); i++) {
        for (size_t j = 0; j < tile[i].size(); j++) {
            player->addCoordinates(x + i, y + j);
        }
    }
    checkAndApplyBonus(player, players, myGrid.getBoard(), x, y);
}

std::string Game::getBiggestSquare(Grid myGrid, std::vector <Player> players) {
    std::vector<std::vector<char>>& grid = myGrid.getBoard();
    int squareSize = 0;
    std::string winingPlayer;
    Player player = players[0];
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            for (size_t playerIndex = 0; playerIndex < players.size(); playerIndex++) {
                if (players[playerIndex].hasCoordinate(i, j)) {
                    player = players[playerIndex];
                }
            }
            if (grid[i][j] == '#') {
                int isSquare = 1;
                int ii = i + 1;
                int jj = j + 1;
                while (isSquare == 1) {
                    for (int iii = i + 1; iii <= ii; iii++) {
                        for (int jjj = j + 1; jjj <= jj; jjj++) {
                            if (grid[iii][jjj] == '.') {
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
    if (tile.empty() || tile[0].empty()) return;

    int rows = tile.size();
    int cols = tile[0].size();

    std::vector<std::vector<char>> rotatedTile(cols, std::vector<char>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotatedTile[j][rows - i - 1] = tile[i][j];
        }
    }

    tile = rotatedTile;

}

void Game::newGame(){
    std::string name;
    int colorChoice;
    int nbPlayer = 0;
    std::vector<Player> players;
    Tiles tiles;
    auto& startingTile = tiles.getStartingTile("tuiles.json");
    std::queue<std::vector<std::vector<char>>> tileQueue = tiles.iniatializeQueue("tuiles.json");
    do {
        std::cout << "Combien de joueurs etes-vous ?" << std::endl;
        std::cin >> nbPlayer;
    } while (nbPlayer > 9 || nbPlayer < 2);

    for (int i = 1; i <= nbPlayer; i++) {
        std::cout << "Quel est votre pseudo ?" << std::endl;
        std::cin >> name;


        Player::displayColorOptions();
        std::cin >> colorChoice;

        Player p1(name, colorChoice);
        players.push_back(p1);

    };

    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << "Joueur : " << players[i].getColorCode() << players[i].getName() << "\033[0m" << std::endl;
    }
    int s = 30;
    if (nbPlayer >= 2 && nbPlayer <= 4) {
        s = 20;
    }
    Grid myGrid(s);
    myGrid.distributeBonuses(nbPlayer);
    myGrid.displayBoard(players);
    Game::startGame(myGrid, &players, startingTile);
    std::cout << "Grid: " << myGrid.getBoard().size() << "\n";
    int totalTurn = 1 * nbPlayer;
    for (int turn = 1; turn <= 3; turn++) {
        std::cout << "Tour numero: " << turn << std::endl;
        for (size_t i = 0; i < players.size(); ++i) {
            char response;
            do {
                std::cout << "Joueur: " << players[i].getName() << std::endl;
                std::cout << "Prendre une tuile (T)\n";
                std::cout << "Echanger la tuile - " << players[i].nbCoupon() << " disponible (E)\n";
                std::cout << "Afficher la file (D)\n";
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
                    std::cout << "Tuile a placer\n";
                    auto tile = tileQueue.front();
                    tileQueue.pop();
                    do {
                        tiles.displayTile(tile);
                        std::cout << "Rotationner la tuile (R)\n";
                        std::cout << "Placer la tuile (P)\n";
                        std::cin >> tileResponse;
                        if (tileResponse == 'r' || tileResponse == 'R') {
                            Game::rotateTileClockwise(tile);
                        }
                        else if (tileResponse == 'p' || tileResponse == 'P') {
                            Game::askUserCoordinates(myGrid, &players[i], players, tile);
                            myGrid.displayBoard(players);
                        }
                    } while (tileResponse != 'p' && tileResponse != 'P');
                }
            } while (response != 't' && response != 'T');
        }
    }
    std::string winner = Game::getBiggestSquare(myGrid, players);
    std::cout << "Le gagnant est: " << winner << std::endl;
}
