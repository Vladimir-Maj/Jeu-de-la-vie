#include "cellSimple.hpp"

CellSimple::CellSimple() : Cell(CellState::DEATH) {};

CellSimple::CellSimple(CellState s) : Cell(s) {};

bool CellSimple::isEditable() { return true; };

void CellSimple::setState(CellState s) { this->state = s; };