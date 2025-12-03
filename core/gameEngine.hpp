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
    std::unique_ptr<Display> renderer;
    int iterationCount;

  public:
    std::unique_ptr<Grid> grid;
    FileManager fm;

    void initialisation(bool useGraphicMode, int iteration) {
        if (useGraphicMode) {
            this->renderer = std::make_unique<Graphic>();
        } else {
            this->renderer = std::make_unique<Console>();
        }

        this->iterationCount = iteration;
    };

    void startSimulation() {
        for (int i = 0; i < this->iterationCount; i++) {
            this->renderer->display(this->grid);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "\n" << std::endl;

            for (int y = 0; y < grid->getHeight(); y++) {
                for (int x = 0; x < grid->getWidth(); x++) {
                    std::vector<Cell *> neighbors = grid->getNeighbors(x, y);
                    Cell *cell = grid->getCell(x, y);
                    int aliveNeighbors = grid->checkCell(neighbors);

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
        };
    };

    void draw() {
        this->renderer->clearScreen();
        this->renderer->display(this->grid);
    };

    void step() {};
    void loadConfig(std::string name) {};
    void save(std::string name) {};
};