#include <iostream>
#include <string>

void afficherRegles()
{
    std::cout << "\nRègles du jeu\n";
    std::cout << "1. Objectif : Créer le plus grand territoire carré sur une grille.\n";
    std::cout << "2. Joueurs : 2 à 9 joueurs.\n";
    std::cout << "   - 2 à 4 joueurs : grille de 20x20.\n";
    std::cout << "   - 5 à 9 joueurs : grille de 30x30.\n";
    std::cout << "3. Déroulement :\n";
    std::cout << "   - Chaque joueur commence avec une tuile 1x1 placée sur la grille.\n";
    std::cout << "   - Les joueurs placent des tuiles en les connectant à leur territoire.\n";
    std::cout << "   - Les tuiles ne peuvent pas toucher les territoires des autres joueurs.\n";
    std::cout << "   - Les joueurs disposent d'un coupon pour échanger une tuile si besoin.\n";
    std::cout << "4. Bonus :\n";
    std::cout << "   - Cases spéciales sur la grille offrant des avantages : échange, pierre, vol.\n";
    std::cout << "5. Fin du jeu :\n";
    std::cout << "   - Après 9 tours, le joueur ayant le plus grand carré gagne.\n";
    std::cout << "   - En cas d'égalité, le nombre total de cases de gazon est pris en compte.\n";
}

void commencerPartie()
{
    std::cout << "Démarrage d'une nouvelle partie\n";
}

void continuerPartie()
{
    std::cout << "Reprise d'une partie en cours\n";
}

int main()
{
    int choix = 0;

    do
    {
        std::cout << "\nMenu principal:\n";
        std::cout << "1. Afficher les règles\n";
        std::cout << "2. Commencer une partie\n";
        std::cout << "3. Continuer une partie\n";
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
            case 3:
                continuerPartie();
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
