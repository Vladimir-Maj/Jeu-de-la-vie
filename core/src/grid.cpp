#include "grid.hpp"
#include "./cells/cellSimple.hpp"
#include <memory>

Grid::Grid(int h, int w) : height(h), width(w) {
    this->cells.resize(h);
    for (int y = 0; y < h; y++) {
        this->cells[y].resize(w);
        for (int x = 0; x < w; x++) {
            this->cells[y][x] = std::make_unique<CellSimple>();
        }
    }
}

Cell *Grid::getCell(int x, int y) { return this->cells[y][x].get(); }

const std::vector<std::vector<std::unique_ptr<Cell>>> &Grid::getCells() const {
    return this->cells;
}

void Grid::setCell(int x, int y, CellState state) {
    cells[y][x]->setState(state);
};

int Grid::getHeight() const { return this->height; }

int Grid::getWidth() const { return this->width; }

std::vector<Cell *> Grid::getNeighbors(int x, int y, bool toric) {
    std::vector<Cell *> neighbors;
    neighbors.reserve(8);

    if (y - 1 >= 0) {
        if (x - 1 >= 0) {
            neighbors.push_back(this->cells[y - 1][x - 1].get());
        }

        neighbors.push_back(this->cells[y - 1][x].get());

        if (x + 1 < this->getWidth()) {
            neighbors.push_back(this->cells[y - 1][x + 1].get());
        }
    } else if (toric) {
        if (x - 1 >= 0) {
            neighbors.push_back(
                this->cells[this->getHeight() - 1][x - 1].get());
        } else {
            neighbors.push_back(
                this->cells[this->getHeight() - 1][this->getWidth() - 1].get());
        }

        neighbors.push_back(this->cells[this->getHeight() - 1][x].get());

        if (x + 1 < this->getWidth()) {
            neighbors.push_back(
                this->cells[this->getHeight() - 1][x + 1].get());
        } else {
            neighbors.push_back(this->cells[this->getHeight() - 1][0].get());
        }
    }

    if (x - 1 >= 0) {
        neighbors.push_back(this->cells[y][x - 1].get());
    } else if (toric) {
        neighbors.push_back(this->cells[y][this->getWidth() - 1].get());
    }

    if (x + 1 < this->getWidth()) {
        neighbors.push_back(this->cells[y][x + 1].get());
    } else if (toric) {
        neighbors.push_back(this->cells[y][0].get());
    }

    if (y + 1 < this->getHeight()) {
        if (x - 1 >= 0) {
            neighbors.push_back(this->cells[y + 1][x - 1].get());
        }

        neighbors.push_back(this->cells[y + 1][x].get());

        if (x + 1 < this->getWidth()) {
            neighbors.push_back(this->cells[y + 1][x + 1].get());
        }
    } else if (toric) {
        if (x - 1 >= 0) {
            neighbors.push_back(this->cells[0][x - 1].get());
        } else {
            neighbors.push_back(this->cells[0][this->getWidth() - 1].get());
        }

        neighbors.push_back(this->cells[0][x].get());

        if (x + 1 < this->getWidth()) {
            neighbors.push_back(this->cells[0][x + 1].get());
        } else {
            neighbors.push_back(this->cells[0][0].get());
        }
    }

    return neighbors;
}

int Grid::checkCell(std::vector<Cell *> neighbors) {
    int alive = 0;

    for (Cell *cell : neighbors) {
        if (cell->getState() == CellState::ALIVE) {
            alive++;
        }
    }

    return alive;
}

void Grid::setCellObject(int x, int y, std::unique_ptr<Cell> cell) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x] = std::move(cell);
    }
}