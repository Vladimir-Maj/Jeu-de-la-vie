#include "appManager.hpp"
#include "gameEngine.hpp"

#include <iostream>
#include <memory>
#include <string>

AppManager::AppManager(int argc, char *argv[]) {
    this->game = std::make_unique<GameEngine>();

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
            this->shouldExit = true;
            this->exitCode = 0;
            return;
        } else if (flag == "-w" || flag == "--width") {
            try {
                this->width = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                this->shouldExit = true;
                this->exitCode = 1;
                return;
            }
        } else if (flag == "-h" || flag == "--height") {
            try {
                this->height = std::stoi(value);
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                this->shouldExit = true;
                this->exitCode = 1;
                return;
            }
        } else if (flag == "-g" || flag == "--graphic") {
            this->useGraphicMode = true;
        } else if (flag == "-lc" || flag == "--loadconfig") {
            if (!this->game->getFileManager().loadConfig(
                    value, this->game->getGrid())) {
                this->shouldExit = true;
                this->exitCode = 1;
                return;
            };
        } else if (flag == "-mc" || flag == "--makeconfig") {
            this->makeconfig = true;
            this->makeConfigPath = value;
        } else if (flag == "-e" || flag == "--edition") {
            this->editionMode = true;
        } else if (flag == "--empty") {
            this->emptyConfig = true;
        } else if (flag == "--toric") {
            this->toricMode = true;
        } else if (flag == "-ic" || flag == "--iterationcount") {
            try {
                this->iterationCount = std::stoi(value);
                if (this->iterationCount < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    this->shouldExit = true;
                    this->exitCode = 1;
                    return;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                this->shouldExit = true;
                this->exitCode = 1;
                return;
            }
        } else if (flag == "-it" || flag == "--iterationtime") {
            try {
                this->iterationTime = std::stoi(value);
                if (this->iterationTime < 0) {
                    std::cerr
                        << "Erreur: la valeur doit être positive pour le flag '"
                        << flag << "'" << std::endl;
                    this->shouldExit = true;
                    this->exitCode = 1;
                    return;
                };
            } catch (const std::exception &e) {
                std::cerr << "Erreur: valeur invalide pour le flag '" << flag
                          << "'" << std::endl;
                this->shouldExit = true;
                this->exitCode = 1;
                return;
            }
        };
    };

    if (this->makeconfig && !this->width) {
        std::cout << "Veuillez indiquer la largeur." << std::endl;
        this->shouldExit = true;
        this->exitCode = 1;
        return;
    } else if (this->makeconfig && !this->height) {
        std::cout << "Veuillez indiquer la hauteur." << std::endl;
        this->shouldExit = true;
        this->exitCode = 1;
        return;
    }

    if (this->makeconfig && !this->game->getFileManager().makeConfig(
                                this->makeConfigPath, this->height, this->width,
                                this->game->getGrid(), this->emptyConfig)) {
        this->shouldExit = true;
        this->exitCode = 1;
        return;
    };
}

int AppManager::execute() {
    if (this->shouldExit) {
        return this->exitCode;
    };

    std::cout << "### INFORMATIONS ###" << std::endl;

    if (this->editionMode) {
        std::cout << " - Mode edition: lance" << std::endl;
    };

    std::cout << " - Regle: " << this->game->getRule()->getName() << std::endl;

    std::cout << " - Affiche: "
              << (this->useGraphicMode ? "Graphique" : "Console") << std::endl;
    std::cout << " - Itération: "
              << (this->iterationCount == 0
                      ? "Infini"
                      : std::to_string(this->iterationCount))
              << std::endl;
    std::cout << " - Fichier config: "
              << this->game->getFileManager().getConfigName() << std::endl;

    if (this->makeconfig) {
        std::cout << " - Largeur de la grille: " << this->width << std::endl;
        std::cout << " - Hauteur de la grille: " << this->height << std::endl;
    }

    this->game->initialisation(this->useGraphicMode, this->iterationCount,
                               this->iterationTime, this->toricMode);

    if (this->useGraphicMode && this->editionMode) {
        this->game->editionMode();
        return 0;
    } else {
        this->game->startSimulation();
        return 0;
    }
};