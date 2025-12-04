#include "display.hpp"

#include <iostream>
#include <memory>

class Console : public Display {
  public:
    void display(std::unique_ptr<Grid> &grid) override {
        this->clearScreen();
        for (int y = 0; y < grid->getHeight(); y++) {
            for (int x = 0; x < grid->getWidth(); x++) {
                Cell *cell = grid->getCell(x, y);
                if (cell->getState()) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    };

    void clearScreen() override { std::cout << "\033[H\033[J"; };
};