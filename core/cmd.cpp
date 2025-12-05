#include "gameEngine.hpp"
#include "cmd.hpp"
#include <iostream>
#include <memory>
#include <string>

cmd::cmd(int argc, char *argv[]) {
    game = std::make_unique<GameEngine>();

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
                      << "\n  --empty"
                      << "\n  --toric"
                      << "\n  -e ou --edition" << std::endl;
            shouldExit = true;
            exitCode = 0;
            return;
        } else if (flag == "-w" || flag == "--width") {
            try {
                width = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                shouldExit = true;
                exitCode = 1;
                return;
            }
        } else if (flag == "-h" || flag == "--height") {
            try {
                height = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                shouldExit = true;
                exitCode = 1;
                return;
            }
        } else if (flag == "-g" || flag == "--graphic") {
            useGraphicMode = true;
        } else if (flag == "-lc" || flag == "--loadconfig") {
            if (!game->getFileManager().loadConfig(value, game->getGrid())) {
                shouldExit = true;
                exitCode = 1;
                return;
            };
        } else if (flag == "-mc" || flag == "--makeconfig") {
            makeconfig = true;
            makeConfigPath = value;
        } else if (flag == "-e" || flag == "--edition") {
            editionMode = true;
        } else if (flag == "--empty") {
            emptyConfig = true;
        } else if (flag == "--toric") {
            toricMode = true;
        } else if (flag == "-ic" || flag == "--iterationcount") {
            try {
                iterationCount = std::stoi(value);
                if (iterationCount < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    shouldExit = true;
                    exitCode = 1;
                    return;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                shouldExit = true;
                exitCode = 1;
                return;
            }
        } else if (flag == "-it" || flag == "--iterationtime") {
            try {
                iterationTime = std::stoi(value);
                if (iterationTime < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    shouldExit = true;
                    exitCode = 1;
                    return;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                shouldExit = true;
                exitCode = 1;
                return;
            }
        };
    };

}

int cmd::run() {
    if (shouldExit) {
        return exitCode;
    }

    if (makeconfig && !width) {
        std::cout << "Veuillez indiquer la largeur." << std::endl;
        return 1;
    } else if (makeconfig && !height) {
        std::cout << "Veuillez indiquer la hauteur." << std::endl;
        return 1;
    }

    if (makeconfig &&
        !game->getFileManager().makeConfig(makeConfigPath, height, width,
                                           game->getGrid(), emptyConfig)) {
        return 1;
    };

    std::cout << "### INFORMATIONS ###" << std::endl;

    if (editionMode) {
        std::cout << " - Mode: Edition" << std::endl;
    };

    std::cout << " - Affiche: " << (useGraphicMode ? "Graphique" : "Console")
              << std::endl;
    std::cout << " - Itération: "
              << (iterationCount == 0 ? "Infini"
                                      : std::to_string(iterationCount))
              << std::endl;
    std::cout << " - Fichier config: " << game->getFileManager().getConfigName()
              << std::endl;

    if (makeconfig) {
        std::cout << " - Largeur de la grille: " << width << std::endl;
        std::cout << " - Hauteur de la grille: " << height << std::endl;
    }

    game->initialisation(useGraphicMode, iterationCount, iterationTime,
                         toricMode);

    if (useGraphicMode && editionMode) {
        game->editionMode();
        return 0;
    } else {
        game->startSimulation();
        return 0;
    }

}