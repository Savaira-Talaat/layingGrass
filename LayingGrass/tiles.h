#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Tiles {
private:
	std::vector<std::vector<char>> matrix;
public:
	void displayTile(const std::vector<std::vector<char>> tuile);
	void displayTileQueue(std::queue<std::vector<std::vector<char>>> tileQueue);
	std::queue<std::vector<std::vector<char>>> iniatializeQueue(const std::string& cheminFichier);
	static std::vector<std::vector<std::vector<char>>> chargerTuiles(const std::string& cheminFichier);
	static std::vector<std::vector<char>>& getStartingTile(const std::string& cheminFichier);
	std::vector<std::vector<char>> getTiles(std::queue<std::vector<std::vector<char>>> tileQueue);
};