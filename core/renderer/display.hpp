#include "main/grid.hpp"

class Display {
  public:
    virtual void display(Grid grid) = 0;
    virtual void refresh() = 0;
};