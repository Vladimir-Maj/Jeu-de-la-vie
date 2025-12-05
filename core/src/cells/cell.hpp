#pragma once

#include "cellState.hpp"

class Cell {
  protected:
    CellState state;

  public:
    Cell();
    Cell(CellState s);

    CellState getState() const;
    virtual void setState(CellState cs) = 0;
    virtual bool isEditable() = 0;

    virtual ~Cell() = default;
};