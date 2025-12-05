#include "cellObstacle.hpp"

CellObstacle::CellObstacle() : Cell(CellState::DEATH) {};

CellObstacle::CellObstacle(CellState s) : Cell(s) {};

bool CellObstacle::isEditable() { return false; };

void CellObstacle::setState(CellState cs) {};