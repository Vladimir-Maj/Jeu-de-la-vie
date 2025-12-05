#include "cell.hpp"
#include "cellState.hpp"

Cell::Cell() : state(CellState::DEATH) {};
Cell::Cell(CellState s) : state(s) {};

CellState Cell::getState() const { return this->state; };