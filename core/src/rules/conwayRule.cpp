#include "conwayRule.hpp"

ConwayRule::ConwayRule() : Rule("Conway") {}

void ConwayRule::useRule(int x, int y, Cell *cell,
                         std::vector<std::vector<CellState>> &newStates,
                         int aliveNeighbors) {
    if (cell->getState() == CellState::ALIVE) {
        if (aliveNeighbors == 2 || aliveNeighbors == 3) {
            newStates[y][x] = CellState::ALIVE;
        } else {
            newStates[y][x] = CellState::DEATH;
        }
    } else {
        if (aliveNeighbors == 3) {
            newStates[y][x] = CellState::ALIVE;
        } else {
            newStates[y][x] = CellState::DEATH;
        }
    }
}