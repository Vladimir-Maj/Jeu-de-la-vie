class Cell {
  private:
    bool state;

  public:
    Cell() : state(false) {};
    Cell(bool s) : state(s) {};

    bool getState() { return this->state; };
    void setState(bool newState) { this->state = newState; };
    bool isAlive() { return false; };
    void toggleState() {};
};