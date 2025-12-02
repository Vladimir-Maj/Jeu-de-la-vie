#include "core/main/fileManager.hpp"
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    int width;
    int height;
    bool graphicMode = false;
    bool makeconfig = false;
    FileManager fm;

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
            graphicMode = true;
        } else if (flag == "-lc" || flag == "--loadconfig") {
            if (!fm.loadConfig(value)) {
                return 1;
            };
        };
    };

    if (!width) {
        std::cout << "Veuillez indiquer la largeur." << std::endl;
        return 1;
    } else if (!height) {
        std::cout << "Veuillez indiquer la hauteur." << std::endl;
        return 1;
    }

    std::cout << "### INFORMATIONS ###" << std::endl;
    std::cout << " - Mode: " << (graphicMode ? "Graphique" : "Console")
              << std::endl;
    std::cout << " - Fichier config: " << fm.getFileName() << std::endl;

    if (makeconfig) {
        std::cout << " - Largeur de la grille: " << width << std::endl;
        std::cout << " - Hauteur de la grille: " << height << std::endl;
    }
};