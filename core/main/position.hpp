class Position {
  private:
    int x;
    int y;

  public:
    Position(int x, int y) : x(x), y(y) {};

    int getX() { return this->x; };
    int getY() { return this->y; };
};