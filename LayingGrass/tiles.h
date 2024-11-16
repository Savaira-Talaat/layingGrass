#pragma once
#include <iostream>
#include <string>
#include <vector>

class Tiles {
private:
	std::vector<std::vector<char>> matrix;
public:
	void afficher();
	static std::vector<std::vector<std::vector<char>>> chargerTuiles(const std::string& cheminFichier);
	static std::vector<std::vector<char>>& getStartingTile(const std::string& cheminFichier);
};