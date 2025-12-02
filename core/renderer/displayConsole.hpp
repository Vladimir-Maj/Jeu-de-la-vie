#include "display.hpp"

class displayConsole : public Display {
  private:
    char livingSymbol;
    char deathSymbol;

  public:
    void display() {};
    void refresh() {};

    void clearScreen() {};
};