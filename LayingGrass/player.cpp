#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include "player.h"
#include "grid.h"

const std::map<int, std::string> colorMap = {
{1, "\033[31m"},
{2, "\033[32m"},
{3, "\033[33m"},
{4, "\033[34m"},
{5, "\033[35m"},
{6, "\033[36m"},
{7, "\033[37m"},
{8, "\033[93m"},
{9, "\033[91m"},
};

Player::Player(std::string name, int colorChoice) {
    this->name = name;
    if (colorMap.find(colorChoice) != colorMap.end()) {
        colorCode = colorMap.at(colorChoice);
    } else {
        colorCode = "\033[37m";
    };
    this->exchangeCoupon = 1;
};

std::string Player::getName() {
    return name;
};

std::string Player::getColorCode() {
    return colorCode;
};

void Player::displayColorOptions() {
    std::cout << "Choose your color: " << std::endl;
    for (const auto& color : colorMap) {
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

void Player::addCoupon() {
    this->exchangeCoupon++;
}

int Player::nbCoupon() {
    return exchangeCoupon;
}

void Player::removeCoupon() {
    exchangeCoupon--;
}

void Player::placeStone(std::vector<std::vector<char>>& board) {
    int x, y;
    std::cout << "Veuillez choisir où placer une pierre (x y) : ";
    std::cin >> x >> y;

    if (board[x][y] == '.') {
        board[x][y] = 'X';
    }
    else {
        std::cout << "Impossible de placer une pierre ici." << std::endl;
    }
}

void Player::stealCouponFromOtherPlayer(std::vector<Player>& players) {
    std::cout << "Choisissez un joueur à voler : " << std::endl;
    for (size_t i = 0; i < players.size(); ++i) {
        if (&players[i] != this) {
            std::cout << i << ": " << players[i].getName() << std::endl;
        }
    }

    int choice;
    std::cin >> choice;

    if (choice >= 0 && choice < players.size() && &players[choice] != this) {
        players[choice].removeCoupon();
        this->addCoupon();
    }
    else {
        std::cout << "Choix invalide !" << std::endl;
    }
}