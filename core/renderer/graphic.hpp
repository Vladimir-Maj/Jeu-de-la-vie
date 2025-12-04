#pragma once
#include "display.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Graphic : public Display {
  private:
    int cellSize;
    int gridWidth;
    int gridHeight;
    std::string title;
    sf::RenderWindow window;

  public:
    Graphic(int cSize, int width, int height, std::string wTitle)
        : cellSize(cSize), gridWidth(width), gridHeight(height), title(wTitle),
          window(sf::VideoMode(sf::Vector2u(width * cSize, height * cSize)),
                 title) {
        window.setVerticalSyncEnabled(true);
        window.setKeyRepeatEnabled(false);
        window.setFramerateLimit(60);
    }

    void display(std::unique_ptr<Grid> &grid) override {
        // --- Événements ---
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Gérer le redimensionnement
            if (event->is<sf::Event::Resized>()) {
                auto size = event->getIf<sf::Event::Resized>();
                // Ajuster la vue pour éviter la déformation
                sf::FloatRect visibleArea(
                    sf::Vector2f(0.f, 0.f),
                    sf::Vector2f(static_cast<float>(size->size.x),
                                 static_cast<float>(size->size.y)));
                window.setView(sf::View(visibleArea));
            }
        }

        // Fond de couleur
        window.clear(sf::Color(30, 30, 30));

        // --- Taille dynamique pour occuper toute la fenêtre ---
        float windowW = static_cast<float>(window.getSize().x);
        float windowH = static_cast<float>(window.getSize().y);
        float scaleX = windowW / static_cast<float>(grid->getWidth());
        float scaleY = windowH / static_cast<float>(grid->getHeight());

        // Taille dynamique (le plus petit pour garder les carrés)
        float cellSizeDynamic = std::min(scaleX, scaleY);

        // Offset pour centrer la grille
        float offsetX = (windowW - cellSizeDynamic * grid->getWidth()) / 2.f;
        float offsetY = (windowH - cellSizeDynamic * grid->getHeight()) / 2.f;

        sf::RectangleShape cell(
            sf::Vector2f(cellSizeDynamic - 1.f, cellSizeDynamic - 1.f));

        // --- Dessin de la grille ---
        for (int x = 0; x < grid->getWidth(); ++x) {
            for (int y = 0; y < grid->getHeight(); ++y) {
                bool alive = grid->getCell(x, y)->getState();
                if (alive) {
                    cell.setFillColor(sf::Color::White);
                    cell.setOutlineThickness(0.f);
                } else {
                    cell.setFillColor(sf::Color::Transparent);
                    cell.setOutlineColor(sf::Color(70, 70, 70));
                    cell.setOutlineThickness(1.f);
                }
                cell.setPosition(sf::Vector2f(offsetX + x * cellSizeDynamic,
                                              offsetY + y * cellSizeDynamic));
                window.draw(cell);
            }
        }

        window.display();
    }
};