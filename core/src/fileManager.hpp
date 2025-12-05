#pragma once

#include "grid.hpp"

#include <filesystem>
#include <memory>

class FileManager {
  private:
    std::filesystem::path configPath;
    std::filesystem::path outputPath;

  public:
    bool loadConfig(std::filesystem::path path,
                    std::unique_ptr<Grid> &gameGrid);

    bool makeConfig(std::filesystem::path path, int height, int width,
                    std::unique_ptr<Grid> &gameGrid, bool isEmptyConfig);

    std::filesystem::path getConfigName() const;
    std::filesystem::path getOutputPath() const;

    void clearOutputFileIfContent();
    void saveOutput(std::unique_ptr<Grid> &grid);
    bool saveConfig(std::unique_ptr<Grid> &grid);
    bool checkSimilarOutputGrid(std::unique_ptr<Grid> &grid);
};
