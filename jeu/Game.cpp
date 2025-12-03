#include "jeu/Game.h"

Game::Game() {
    std::cout << "Choisissez le fichier a consommer: ";
    std::cin >> fichierEntree0;
    fichierEntree = std::string("out/entree/") + fichierEntree0 + std::string(".txt");

    if (!std::ifstream(fichierEntree).is_open()) {
        std::cout << "LECTURE : fichier INVALIDE" << std::endl;
        exit(0);
    }

    std::cout<< "grille Classique lancée confirmé avec '0': ";
    std::cin >> choixGrille;


    std::cout << "Mode Console confirmé avec 0: ";
    std::cin >> modeConsole;

    std::cout << "Choisissez le nombre d'iterations (nombre entier): ";
    std::cin >> iterations;
    if ((iterations >= 40) && (modeConsole==0)){
        std::cout << "DANGER : ITERATIONS TROP NOMBREUSES - EXIT" << std::endl;
        exit(0);
    }

    if (modeConsole) {
        std::cout << "Choisissez le temps entre iterations en millisecondes: ";
        std::cin >> delai;
    }
}

void Game::lancer() {
    GrilleClassique existance(fichierEntree);
    if (!choixGrille){
        std::cout<<"Classique"<<std::endl;
        existance.lireFichier();
        if (!modeConsole){
            existance.iteration(iterations, modeConsole);
            std::cout << std::endl;
    }
    else{
        std::cout << "comment tu sais que cette condition existe, ce mode Graphique est en construction donc va t'en" << std::endl;
    }
  }
}
