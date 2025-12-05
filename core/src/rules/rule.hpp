#pragma once

#include "../cells/cell.hpp"
#include "../cells/cellState.hpp"
#include <string>
#include <vector>

class Rule {
  private:
    std::string name;

  public:
    Rule(const std::string ruleName);

    std::string getName() const;

    virtual void useRule(int x, int y, Cell *cell,
                         std::vector<std::vector<CellState>> &newStates,
                         int aliveNeighbors) = 0;
};