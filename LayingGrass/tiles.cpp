#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <random>
#include "json.hpp"
#include "tiles.h"

using json = nlohmann::json;

std::vector<std::vector<char>>& Tiles::getStartingTile(const std::string& cheminFichier) {
    static auto tuiles = chargerTuiles(cheminFichier); 
    if (!tuiles.empty()) {  
        return tuiles[0];  
    }
    else {
        throw std::runtime_error("Le fichier de tuiles est vide ou n'a pas pu être chargé.");
    }
}

void Tiles::displayTile(const std::vector<std::vector<char>> tuile) {
    for (size_t i = 0; i < tuile.size(); i++) {
        for (char cell : tuile[i]) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

std::queue<std::vector<std::vector<char>>> Tiles::iniatializeQueue(const std::string& cheminFichier) {
    auto tiles = chargerTuiles(cheminFichier);
    std::queue<std::vector<std::vector<char>>> tileQueue;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tiles.begin(), tiles.end(), g);

    for (const auto& tile : tiles) {
        tileQueue.push(tile);
    }
    return tileQueue;

}

void Tiles::displayTileQueue(std::queue<std::vector<std::vector<char>>> tileQueue) {
    std::queue<std::vector<std::vector<char>>> tempQueue = tileQueue;
    std::cout << "Contenu de tileQueue :\n";
    int i = 0;
    while (!tempQueue.empty() && i<10) {
        auto tuile = tempQueue.front();
        tempQueue.pop();

        displayTile(tuile);
        std::cout << "----------\n";
        i++;
    }
}

std::vector<std::vector<char>> Tiles::getTiles(std::queue<std::vector<std::vector<char>>> tileQueue) {
    if (tileQueue.empty()) {
        throw std::runtime_error("Aucune tuile restante dans la file d'attente.");
    }

    auto tile = tileQueue.front();
    tileQueue.pop();
    return tile;
}


std::vector<std::vector<std::vector<char>>> Tiles::chargerTuiles(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);

    json jsonData;
    fichier >> jsonData;

    std::vector<std::vector<std::vector<char>>> tuiles;

    for (const auto& tuileJson : jsonData["tuiles"]) {
        std::vector<std::vector<char>> tuile;
        for (const auto& ligne : tuileJson["matrice"]) {
            std::vector<char> ligneTuile;
            for (const auto& cell : ligne) {
                ligneTuile.push_back(cell.get<std::string>()[0]); 
            }
            tuile.push_back(ligneTuile);
        }
        tuiles.push_back(tuile);
    }

    return tuiles;
}
