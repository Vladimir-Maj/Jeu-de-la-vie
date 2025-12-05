#include "gameEngine.hpp"

void GameEngine::initialisation(bool useGraphicMode, int iCount, int iTime,
                                bool toric) {
    if (useGraphicMode) {
        this->renderer = std::make_unique<Graphic>(10, 80, 80, "Jeu de la vie");
    } else {
        this->renderer = std::make_unique<Console>();
    }

    this->graphicMode = useGraphicMode;
    this->iterationCount = iCount;
    this->iterationTime = iTime;
    this->toricMode = toric;
}

void GameEngine::startSimulation() {

    if (!this->graphicMode) {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

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
        }
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
        }
    }
}

void GameEngine::simulation() {
    fm.saveOutput(this->grid);

    this->renderer->display(this->grid);
    std::this_thread::sleep_for(std::chrono::milliseconds(this->iterationTime));

    std::vector<std::vector<CellState>> newStates(
        this->grid->getHeight(),
        std::vector<CellState>(this->grid->getWidth()));

    for (int y = 0; y < this->grid->getHeight(); y++) {
        for (int x = 0; x < this->grid->getWidth(); x++) {
            Cell *cell = this->grid->getCell(x, y);

            if (!cell->isEditable()) {
                newStates[y][x] = cell->getState();
                continue;
            }

            std::vector<Cell *> neighbors =
                this->grid->getNeighbors(x, y, this->toricMode);
            int aliveNeighbors = this->grid->checkCell(neighbors);

            if (cell->getState() == CellState::ALIVE) {
                if (aliveNeighbors == 2 || aliveNeighbors == 3) {
                    newStates[y][x] = CellState::ALIVE;
                } else {
                    newStates[y][x] = CellState::DEATH;
                }
            } else {
                if (aliveNeighbors == 3) {
                    newStates[y][x] = CellState::ALIVE;
                } else {
                    newStates[y][x] = CellState::DEATH;
                }
            }
        }
    }

    for (int y = 0; y < this->grid->getHeight(); y++) {
        for (int x = 0; x < this->grid->getWidth(); x++) {
            this->grid->setCell(x, y, newStates[y][x]);
        }
    }
}

void GameEngine::draw() {
    this->renderer->clearScreen();
    this->renderer->display(this->grid);
}

void GameEngine::editionMode() {
    return this->renderer->editionMode(this, this->grid);
}

std::unique_ptr<Grid> &GameEngine::getGrid() { return this->grid; }

FileManager &GameEngine::getFileManager() { return this->fm; }