#pragma once

#include "main/grid.hpp"

class Display {
  public:
    virtual void display(std::unique_ptr<Grid> &grid) = 0;
    virtual void refresh() = 0;
    virtual void clearScreen() {};
};