#include "position.hpp";

class Cell {
  private:
    bool state;
    Position position;

  public:
    Cell(bool etat, Position pos) : state(state), position(pos) {};

    bool getEtat() { return this->state; };
    void setEtat(bool newState) { this->state = newState; };
    bool isAlive() { return false; };
    void toggleState() {};
};