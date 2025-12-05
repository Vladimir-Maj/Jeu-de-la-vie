#pragma once

#include "gameEngine.hpp"

#include <memory>
#include <string>

class AppManager {
  private:
    int width = 0;
    int height = 0;
    bool useGraphicMode = false;
    bool makeconfig = false;
    std::string makeConfigPath;
    int iterationCount = 0;
    int iterationTime = 250;
    bool editionMode = false;
    bool emptyConfig = false;
    bool toricMode = false;

    bool shouldExit = false;
    int exitCode = 0;

    std::unique_ptr<GameEngine> game;

  public:
    AppManager(int argc, char *argv[]);
    int execute();
};