#include "main/fileManager.hpp"
#include "main/grid.hpp"
#include "renderer/console.hpp"
#include "renderer/display.hpp"
#include "renderer/graphic.hpp"
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

  public:
    void initialisation(bool useGraphicMode, int iCount = 0, int iTime = 250,
                        bool toric = false) {
        if (useGraphicMode) {
            this->renderer =
                std::make_unique<Graphic>(10, 80, 80, "Jeu de la vie");
        } else {
            this->renderer = std::make_unique<Console>();
        }

        this->iterationCount = iCount;
        this->iterationTime = iTime;
        this->toricMode = toric;
    };

    void startSimulation() {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        int similarOutputGrids = 0;

        if (iterationCount == 0) {
            while (true) {
                simulation();

                if (fm.checkSimilarOutputGrid(this->grid)) {
                    similarOutputGrids++;
                } else {
                    similarOutputGrids = 0;
                }

                if (similarOutputGrids == 3) {
                    break;
                }
            };
        } else {
            for (int i = 0; i < this->iterationCount; i++) {
                simulation();

                if (fm.checkSimilarOutputGrid(this->grid)) {
                    similarOutputGrids++;
                } else {
                    similarOutputGrids = 0;
                }

                if (similarOutputGrids == 3) {
                    break;
                }
            };
        };
    };

    void simulation() {
        fm.saveOutput(this->grid);

        this->renderer->display(this->grid);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(this->iterationTime));

        std::vector<std::vector<Cell>> tmpCells = this->grid->getCells();

        for (int y = 0; y < this->grid->getHeight(); y++) {
            for (int x = 0; x < this->grid->getWidth(); x++) {
                Cell *cell = &tmpCells[y][x];

                if (cell->isObstacle()) {
                    continue;
                }

                std::vector<Cell *> neighbors =
                    this->grid->getNeighbors(x, y, this->toricMode);
                int aliveNeighbors = this->grid->checkCell(neighbors);

                if (cell->getState()) {
                    if (aliveNeighbors != 2 && aliveNeighbors != 3) {
                        cell->setState(0);
                    };
                } else {
                    if (aliveNeighbors == 3) {
                        cell->setState(1);
                    };
                };
            };
        };

        for (int y = 0; y < this->grid->getHeight(); y++) {
            for (int x = 0; x < this->grid->getWidth(); x++) {
                Cell *cell = this->grid->getCell(x, y);
                cell->setState(tmpCells[y][x].getState());
            };
        };
    }

    void draw() {
        this->renderer->clearScreen();
        this->renderer->display(this->grid);
    };

    bool editionMode() { return this->renderer->editionMode(this->grid); };

    std::unique_ptr<Grid> &getGrid() { return this->grid; };
    FileManager &getFileManager() { return this->fm; };
};