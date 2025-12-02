#include "main/grid.hpp"
#include "main/rule.hpp"
#include "main/stateManager.hpp"
#include "renderer/display.hpp"

class Automate {
  private:
    Grid grid;
    Rule rule;
    Display *display = nullptr;
    StateManager stateManager;

  public:
    void initialisation(int w, int h) {};
    void step() {};
    void draw() {};
    void loadConfig(std::string name) {};
    void save(std::string name) {};
};