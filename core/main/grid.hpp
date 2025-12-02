#include "cell.hpp"
#include <vector>

class Grid {
  private:
    int width;
    int height;
    std::vector<Cell> cells;
    int generation;

  public:
    Grid(int w, int h) : width(w), height(h) {};

    // Cell getCell(int x, int y) {};
    void setCell(int x, int y, bool state) {};

    int getWidth() { return this->width; };
    int getHeight() { return this->height; };

    int countNeighbors(int x, int y) { return 0; };
    int getGeneration() { return 0; };
    // Grid clone() {};
};