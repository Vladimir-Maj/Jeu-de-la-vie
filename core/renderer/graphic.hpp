#pragma once

#include "display.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class GameEngine;

class Graphic : public Display {
  private:
    int cellSize;
    int gridWidth;
    int gridHeight;
    std::string title;
    sf::RenderWindow window;
    sf::RectangleShape cell;

    void windowResize(const sf::Event::Resized *size);
    float calculateCellSize(const std::unique_ptr<Grid> &grid, float &offsetX,
                            float &offsetY) const;
    void drawGrid(std::unique_ptr<Grid> &grid, float cellSizeDynamic,
                  float offsetX, float offsetY);
    bool mouseClick(const sf::Event::MouseButtonPressed *mouse,
                    const std::unique_ptr<Grid> &grid, float cellSizeDynamic,
                    float offsetX, float offsetY);

  public:
    Graphic(int cSize, int width, int height, std::string wTitle);

    void display(std::unique_ptr<Grid> &grid) override;
    void editionMode(GameEngine *game, std::unique_ptr<Grid> &grid) override;
};
