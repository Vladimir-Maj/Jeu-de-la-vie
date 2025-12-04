#include "core/gameEngine.hpp"
#include "core/main/fileManager.hpp"
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    int width;
    int height;
    bool useGraphicMode = false;
    bool makeconfig = false;
    int iterationCount;
    int iterationTime = 250;

    GameEngine game;

    for (int i = 1; i < argc; i++) {
        std::string flag = argv[i];
        std::string value = (i + 1 < argc ? argv[i + 1] : "");

        if (flag == "--help") {
            std::cout << "Utilisation:"
                      << "\n  -lc ou --loadconfig <chemin>"
                      << "\n  -mc ou --makeconfig <chemin>"
                      << "\n  -w ou --width <largeur>"
                      << "\n  -h ou --height <hauteur>"
                      << "\n  -g ou --graphic (terminal par defaut)"
                      << "\n  -ic ou --iterationcount <nombre>"
                      << "\n  -it ou --iterationtime <millisecondes>"
                      << std::endl;
            return 0;
        } else if (flag == "-w" || flag == "--width") {
            try {
                width = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                return 1;
            }
        } else if (flag == "-h" || flag == "--height") {
            try {
                height = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                return 1;
            }
        } else if (flag == "-g" || flag == "--graphic") {
            useGraphicMode = true;
        } else if (flag == "-lc" || flag == "--loadconfig") {
            if (!game.getFileManager().loadConfig(value, game.getGrid())) {
                return 1;
            };
        } else if (flag == "-ic" || flag == "--iterationcount") {
            try {
                iterationCount = std::stoi(value);
                if (iterationCount < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    return 1;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                return 1;
            }
        } else if (flag == "-it" || flag == "--iterationtime") {
            try {
                iterationTime = std::stoi(value);
                if (iterationTime < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    return 1;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                return 1;
            }
        };
    };

    if (makeconfig && !width) {
        std::cout << "Veuillez indiquer la largeur." << std::endl;
        return 1;
    } else if (makeconfig && !height) {
        std::cout << "Veuillez indiquer la hauteur." << std::endl;
        return 1;
    }

    std::cout << "### INFORMATIONS ###" << std::endl;
    std::cout << " - Mode: " << (useGraphicMode ? "Graphique" : "Console")
              << std::endl;
    std::cout << " - Fichier config: " << game.getFileManager().getFileName()
              << std::endl;

    if (makeconfig) {
        std::cout << " - Largeur de la grille: " << width << std::endl;
        std::cout << " - Hauteur de la grille: " << height << std::endl;
    }

    game.initialisation(useGraphicMode, iterationCount, iterationTime);
    game.startSimulation();
};