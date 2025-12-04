#pragma once

#include "cell.hpp"
#include <vector>

class Grid {
  private:
    int height;
    int width;
    std::vector<std::vector<Cell>> cells;

  public:
    Grid(int h, int w) : height(h), width(w) {
        this->cells.resize(h);
        for (int y = 0; y < h; y++) {
            this->cells[y].resize(w);
        }
    };

    Cell *getCell(int x, int y) { return &this->cells[y][x]; };
    std::vector<std::vector<Cell>> getCells() { return this->cells; };
    void setCell(int x, int y, bool state) { cells[y][x].setState(state); };

    int getHeight() const { return this->height; };
    int getWidth() const { return this->width; };

    std::vector<Cell *> getNeighbors(int x, int y, bool toric) {
        std::vector<Cell *> neighbors;
        neighbors.reserve(8);

        if (y - 1 >= 0) {
            if (x - 1 >= 0) {
                neighbors.push_back(&this->cells[y - 1][x - 1]);
            }

            neighbors.push_back(&this->cells[y - 1][x]);

            if (x + 1 < this->getWidth()) {
                neighbors.push_back(&this->cells[y - 1][x + 1]);
            }
        } else if (toric) {
            if (x - 1 >= 0) {
                neighbors.push_back(&this->cells[this->getHeight() - 1][x - 1]);
            } else {
                neighbors.push_back(
                    &this->cells[this->getHeight() - 1][this->getWidth() - 1]);
            }

            neighbors.push_back(&this->cells[this->getHeight() - 1][x]);

            if (x + 1 < this->getWidth()) {
                neighbors.push_back(&this->cells[this->getHeight() - 1][x + 1]);
            } else {
                neighbors.push_back(&this->cells[this->getHeight() - 1][0]);
            }
        };

        if (x - 1 >= 0) {
            neighbors.push_back(&this->cells[y][x - 1]);
        } else if (toric) {
            neighbors.push_back(&this->cells[y][this->getWidth() - 1]);
        };

        if (x + 1 < this->getWidth()) {
            neighbors.push_back(&this->cells[y][x + 1]);
        } else if (toric) {
            neighbors.push_back(&this->cells[y][0]);
        };

        if (y + 1 < this->getHeight()) {
            if (x - 1 >= 0) {
                neighbors.push_back(&this->cells[y + 1][x - 1]);
            }

            neighbors.push_back(&this->cells[y + 1][x]);

            if (x + 1 < this->getWidth()) {
                neighbors.push_back(&this->cells[y + 1][x + 1]);
            }
        } else if (toric) {
            if (x - 1 >= 0) {
                neighbors.push_back(&this->cells[0][x - 1]);
            } else {
                neighbors.push_back(&this->cells[0][this->getWidth() - 1]);
            }

            neighbors.push_back(&this->cells[0][x]);

            if (x + 1 < this->getWidth()) {
                neighbors.push_back(&this->cells[0][x + 1]);
            } else {
                neighbors.push_back(&this->cells[0][0]);
            }
        };

        return neighbors;
    };

    int checkCell(std::vector<Cell *> neighbors) {
        int alive = 0;

        for (Cell *cell : neighbors) {
            if (cell->getState()) {
                alive++;
            };
        };

        return alive;
    };
};