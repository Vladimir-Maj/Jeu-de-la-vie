#pragma once

#include "main/grid.hpp"

class Display {
  public:
    virtual void display(std::unique_ptr<Grid> &grid) = 0;
    virtual void clearScreen() {};
    virtual bool editionMode(std::unique_ptr<Grid> &grid) {};
};