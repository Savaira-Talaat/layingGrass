#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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

void Tiles::afficher() {
    for (const auto& ligne : matrix) {
        for (char cell : ligne) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}


void afficherTuile(const std::vector<std::vector<char>>& tuile) {
    for (const auto& ligne : tuile) {
        for (char cell : ligne) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
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
