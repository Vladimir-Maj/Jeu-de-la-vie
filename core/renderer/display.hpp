#pragma once

#include "main/grid.hpp"
#include <memory>

class GameEngine;

class Display {
  public:
    virtual void display(std::unique_ptr<Grid> &grid) = 0;
    virtual void clearScreen() {};
    virtual void editionMode(GameEngine *game, std::unique_ptr<Grid> &grid) {};
};