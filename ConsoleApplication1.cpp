#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.h"

// Fonction pour afficher une tuile
void afficherTuile(const std::vector<std::vector<char>>& tuile) {
    for (const auto& ligne : tuile) {
        for (char cell : ligne) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}
/*
// Fonction pour charger les tuiles depuis un fichier JSON
std::vector<std::vector<std::vector<char>>> chargerTuiles(const std::string& cheminFichier) {
    // Ouvrir le fichier JSON
    std::ifstream fichier(cheminFichier);
    std::stringstream buffer;
    buffer << fichier.rdbuf();

    Json::Value jsonData;
    buffer >> jsonData;  // Utilisation de jsoncpp pour analyser le fichier

    std::vector<std::vector<std::vector<char>>> tuiles;

    // Extraire les tuiles du JSON
    for (const auto& tuileJson : jsonData["tuiles"]) {
        std::vector<std::vector<char>> tuile;
        for (const auto& ligne : tuileJson["matrice"]) {
            std::vector<char> ligneTuile;
            for (const auto& cell : ligne) {
                ligneTuile.push_back(cell.asChar());  // Convertir en char
            }
            tuile.push_back(ligneTuile);
        }
        tuiles.push_back(tuile);
    }

    return tuiles;
}
*/

void test() {
    std::ifstream file("tuiles.json");
    nlohmann::json data = nlohmann::json::parse(file);
    std::string tile = data["tuiles"][0]["matrice"].dump();
    std::cout << tile << std::endl;
}
int main() {

    // Afficher les tuiles
    /*auto tuiles = chargerTuiles("tuiles.json");
    int compteur = 1;
    for (const auto& tuile : tuiles) {
        std::cout << "Tuile " << compteur++ << " :\n";
        afficherTuile(tuile);
        std::cout << "\n";
    }*/
    test();

    return 0;
}