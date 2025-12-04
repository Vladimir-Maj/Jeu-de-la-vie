class Cell {
  private:
    bool state;
    bool obstacle;

  public:
    Cell() : state(false), obstacle(false) {};
    Cell(bool s, bool o) : state(s), obstacle(o) {};

    bool getState() { return this->state; };
    void setState(bool newState) { this->state = newState; };

    bool isObstacle() { return this->obstacle; };
    void setObstacle(bool obstacle) { this->obstacle = obstacle; };
};