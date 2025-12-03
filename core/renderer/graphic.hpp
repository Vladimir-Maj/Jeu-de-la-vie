#pragma once

#include "display.hpp"

class Graphic : public Display {
  public:
    void display(std::unique_ptr<Grid> &grid) override {};
    void refresh() override {};

    void manageEvents() {};
};