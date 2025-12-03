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

        outputPath =
            "data/outputs/" + this->getFileName().stem().string() + "_out.txt";
        return true;
    };

    std::filesystem::path getFileName() const {
        return this->filePath.filename();
    };

    void makeOutput() {
        bool status = std::filesystem::copy_file(
            this->filePath,
            "data/outputs/" + this->getFileName().stem().string() + "_out.txt",
            std::filesystem::copy_options::overwrite_existing);
        if (!status) {
            std::cerr << "Erreur: problème lors de la création du fichier de "
                         "sortie"
                      << std::endl;
        };
    };

    void save(std::unique_ptr<Grid> &grid) {
        std::ofstream file(this->outputPath);

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

        file.close();
    };
};