#pragma once

#include "display.hpp"
#include <memory>

class Console : public Display {
  public:
    void display(std::unique_ptr<Grid> &grid) override;
    void clearScreen() override;
};
