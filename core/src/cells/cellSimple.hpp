#include "cell.hpp"
#include "cellState.hpp"

class CellSimple : public Cell {
  public:
    CellSimple();
    CellSimple(CellState s);

    bool isEditable() override;
    void setState(CellState s);
};