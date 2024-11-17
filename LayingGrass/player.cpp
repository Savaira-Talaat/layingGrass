﻿#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include "player.h"
#include "grid.h"

const std::map<int, std::string> colorMap = {
{1, "\033[31m"}, // rouge
{2, "\033[32m"}, // vert
{3, "\033[33m"}, // jaune
{4, "\033[34m"}, // bleu
{5, "\033[35m"}, // magenta
{6, "\033[36m"}, // cyan
{7, "\033[37m"}, // blanc
{8, "\033[93m"}, // jaune clair
{9, "\033[91m"}, // saumon
};

Player::Player(std::string name, int colorChoice) {
    this->name = name;
    if (colorMap.find(colorChoice) != colorMap.end()) {
        colorCode = colorMap.at(colorChoice);
    } else {
        colorCode = "\033[37m";
    };
};

std::string Player::getName() {
    return name;
};

std::string Player::getColorCode() {
    return colorCode;
};

void Player::displayColorOptions() {
    std::cout << "Choose your color: " << std::endl;
    for (const auto& color : colorMap) { //le auto permet au compilateur de trouver automatiquement le type d'une variable et & c'est juste pour dire que la variable sera une valeur de réf à l'objet qu'elle représente et non une copie.
                                       //(La référence permet directement d'accéder à l'objet original ce qui économise la mémoire et les copies couteuses)
        std::cout << color.first << ": " << color.second << "Color" << "\033[0m" << std::endl;
    }
}

void Player::addCoordinates(int x, int y) {
    coordinates.emplace_back(x, y);
}

std::vector<std::pair<int, int>> Player::getCoordinates() {
    return coordinates;
}

bool Player::hasCoordinate(int x, int y) const {
    for (const auto& coord : coordinates) {
        if (coord.first == x && coord.second == y) {
            return true;
        }
    }
    return false;
}

void Player::displayColor() {
    std::cout << "Coordonnées pour le joueur : " << name << std::endl;
    for (const auto& coord : coordinates) {
        std::cout << "(" << coord.first << ", " << coord.second << ")" << std::endl;
    }
}
