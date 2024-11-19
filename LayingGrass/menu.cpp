#include <iostream>
#include <string>
#include "game.h"

void afficherRegles()
{
    std::cout << "\nRegles du jeu\n";
    std::cout << "1. Objectif : Creer le plus grand territoire carre sur une grille.\n";
    std::cout << "2. Joueurs : 2 à 9 joueurs.\n";
    std::cout << "   - 2 à 4 joueurs : grille de 20x20.\n";
    std::cout << "   - 5 à 9 joueurs : grille de 30x30.\n";
    std::cout << "3. Deroulement :\n";
    std::cout << "   - Chaque joueur commence avec une tuile 1x1 placee sur la grille.\n";
    std::cout << "   - Les joueurs placent des tuiles en les connectant à leur territoire.\n";
    std::cout << "   - Les tuiles ne peuvent pas toucher les territoires des autres joueurs.\n";
    std::cout << "   - Les joueurs disposent d'un coupon pour echanger une tuile si besoin.\n";
    std::cout << "4. Bonus :\n";
    std::cout << "   - Cases speciales sur la grille offrant des avantages : echange, pierre, vol.\n";
    std::cout << "5. Fin du jeu :\n";
    std::cout << "   - Apres 9 tours, le joueur ayant le plus grand carre gagne.\n";
    std::cout << "   - En cas d'egalite, le nombre total de cases de gazon est pris en compte.\n";
}

void commencerPartie()
{
    Game::newGame();
}

int main()
{
    int choix = 0;

    do
    {
        std::cout << "\nMenu principal:\n";
        std::cout << "1. Afficher les regles\n";
        std::cout << "2. Commencer une partie\n";
        std::cout << "0. Quitter\n";
        std::cout << "Faites votre choix : ";
        std::cin >> choix;

        switch (choix)
        {
            case 1:
                afficherRegles();
                break;
            case 2:
                commencerPartie();
                break;
            case 0:
                std::cout << "Au revoir !\n";
                break;
            default:
                std::cout << "Choix invalide, veuillez réessayer.\n";
                break;
        }
    } while (choix != 0);

    return 0;
}
