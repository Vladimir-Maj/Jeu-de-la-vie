#pragma once

#include "cell.hpp"
#include "cellState.hpp"

class CellObstacle : public Cell {
  public:
    CellObstacle();
    CellObstacle(CellState s);

    bool isEditable() override;
    void setState(CellState cs) override;
};