#pragma once

#include "cells/cell.hpp"

#include <memory>
#include <vector>

class Grid {
  private:
    int height;
    int width;
    std::vector<std::vector<std::unique_ptr<Cell>>> cells;

  public:
    Grid(int h, int w);

    Cell *getCell(int x, int y);
    const std::vector<std::vector<std::unique_ptr<Cell>>> &getCells() const;
    void setCell(int x, int y, CellState state);
    void setCellObject(int x, int y, std::unique_ptr<Cell> cell);

    int getHeight() const;
    int getWidth() const;

    std::vector<Cell *> getNeighbors(int x, int y, bool toric);
    int checkCell(std::vector<Cell *> neighbors);
};