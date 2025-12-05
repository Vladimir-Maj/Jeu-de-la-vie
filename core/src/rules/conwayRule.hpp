#pragma once

#include "rule.hpp"

class ConwayRule : public Rule {
  public:
    ConwayRule();
    void useRule(int x, int y, Cell *cell,
                 std::vector<std::vector<CellState>> &newStates,
                 int aliveNeighbors) override;
};