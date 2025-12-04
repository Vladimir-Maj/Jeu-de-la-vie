#pragma once

#include "grid.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

class FileManager {
  private:
    std::filesystem::path filePath;
    std::filesystem::path outputPath;
    std::unique_ptr<Grid> gridLoadedFromConfig;

  public:
    bool loadConfig(std::filesystem::path path,
                    std::unique_ptr<Grid> &gameGrid) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Erreur: chemin de la configuration inexistant"
                      << std::endl;
            return false;
        };

        this->filePath = path;
        std::ifstream file(this->filePath);

        if (!file.is_open()) {
            std::cerr << "Erreur: problème lors de l'ouverture du fichier"
                      << std::endl;
            return false;
        };

        std::string line;
        int height, width;
        if (!std::getline(file, line)) {
            std::cerr << "Erreur: fichier config vide" << std::endl;
            return false;
        } else {
            std::istringstream size(line);
            if (!(size >> height >> width)) {
                std::cerr << "Erreur: le format n'est pas respecté -> <height> "
                             "<width>"
                          << std::endl;
                return false;
            } else if (height <= 0 || width <= 0) {
                std::cerr << "Erreur: les valeurs doivent être positives"
                          << std::endl;
                return false;
            };
        };

        gameGrid = std::make_unique<Grid>(height, width);

        for (int y = 0; y < height; y++) {
            if (!std::getline(file, line)) {
                std::cerr << "Erreur: colonne manquante -> y = " << y
                          << std::endl;
                return false;
            };

            std::istringstream lineContent(line);
            for (int x = 0; x < width; x++) {
                int value;
                if (!(lineContent >> value)) {
                    std::cerr << "Erreur: valeur manquante -> x = " << x
                              << std::endl;
                    return false;
                } else if (value != 0 && value != 1) {
                    std::cerr
                        << "Erreur: la valeur doit être 0 ou 1 -> (y=" << y
                        << ", x=" << x << ")" << value << std::endl;
                    return false;
                }

                gameGrid->setCell(x, y, value);
            };

            int outOfRangeWidth;
            if (lineContent >> outOfRangeWidth) {
                std::cerr << "Erreur: colonne en trop" << std::endl;
                return false;
            };
        };

        if (std::getline(file, line)) {
            std::cerr << "Erreur: ligne en trop" << std::endl;
            return false;
        };

        outputPath = "../data/outputs/" + this->getFileName().stem().string() +
                     "_out.txt";
        this->clearOutputFileIfContent();
        return true;
    };

    std::filesystem::path getFileName() const {
        return this->filePath.filename();
    };

    void clearOutputFileIfContent() {
        if (std::filesystem::exists(this->outputPath)) {
            std::ofstream file(this->outputPath, std::ios::trunc);
            file.close();
        };
    };

    void save(std::unique_ptr<Grid> &grid) {
        std::ofstream file(this->outputPath, std::ios::app);

        if (!file.is_open()) {
            std::cerr << "Erreur: problème lors de l'ouverture du fichier"
                      << std::endl;
            return;
        };

        for (int y = 0; y < grid->getHeight(); y++) {
            for (int x = 0; x < grid->getWidth(); x++) {
                file << (grid->getCell(x, y)->getState() ? "1" : "0") << " ";
            }
            file << std::endl;
        };
        file << std::endl;

        file.close();
    };

    bool checkSimilarOutputGrid(std::unique_ptr<Grid> &grid) {
        if (!std::filesystem::exists(this->outputPath)) {
            std::cerr << "Erreur: le fichier de sortie n'existe pas"
                      << std::endl;
            return false;
        }

        std::ifstream file(this->outputPath);
        if (!file.is_open()) {
            std::cerr << "Erreur: problème lors de l'ouverture du fichier"
                      << std::endl;
            return false;
        }

        std::vector<std::string> fullLines;
        std::string line;
        while (std::getline(file, line)) {
            fullLines.push_back(line);
        }
        file.close();

        if (fullLines.empty()) {
            std::cerr << "Erreur: fichier vide" << std::endl;
            return false;
        }

        std::vector<std::string> lastBlock;
        for (int i = fullLines.size() - 1; i >= 0; i--) {
            if (fullLines[i].empty() || fullLines[i].find_first_not_of(
                                            " \t\r\n") == std::string::npos) {
                if (!lastBlock.empty()) {
                    break;
                }
                continue;
            }
            lastBlock.insert(lastBlock.begin(), fullLines[i]);
        }

        if (lastBlock.empty()) {
            std::cerr << "Erreur: aucun bloc trouvé" << std::endl;
            return false;
        }

        if (lastBlock.size() != grid->getHeight()) {
            return false;
        }

        for (int y = 0; y < grid->getHeight(); y++) {
            std::istringstream lastIteration(lastBlock[y]);
            for (int x = 0; x < grid->getWidth(); x++) {
                int value;
                if (!(lastIteration >> value)) {
                    return false;
                }
                if (value != grid->getCell(x, y)->getState()) {
                    return false;
                }
            }
        }

        return true;
    };
};