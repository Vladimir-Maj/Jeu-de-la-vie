#pragma once

#include "renderer/console.hpp"
#include "renderer/display.hpp"
#include "renderer/graphic.hpp"
#include "src/fileManager.hpp"
#include "src/grid.hpp"

#include <chrono>
#include <memory>
#include <thread>

class GameEngine {
  private:
    std::unique_ptr<Grid> grid;
    std::unique_ptr<Display> renderer;
    FileManager fm;
    int iterationCount;
    int iterationTime;
    bool toricMode;
    bool graphicMode;

  public:
    void initialisation(bool useGraphicMode, int iCount = 0, int iTime = 250,
                        bool toric = false);

    void startSimulation();
    void simulation();
    void draw();
    void editionMode();

    std::unique_ptr<Grid> &getGrid();
    FileManager &getFileManager();
};