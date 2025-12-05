#include "console.hpp"
#include <iostream>

void Console::display(std::unique_ptr<Grid> &grid) {
    this->clearScreen();
    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Cell *cell = grid->getCell(x, y);
            if (cell->getState() == CellState::ALIVE) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            };
        };
        std::cout << std::endl;
    };
};

void Console::clearScreen() { std::cout << "\033[H\033[J"; };
