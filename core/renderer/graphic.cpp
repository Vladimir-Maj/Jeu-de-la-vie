#include "graphic.hpp"
#include "../core/gameEngine.hpp"
#include "../src/cells/cellObstacle.hpp"
#include "../src/cells/cellSimple.hpp"

#include <iostream>

Graphic::Graphic(int cSize, int width, int height, std::string wTitle)
    : cellSize(cSize), gridWidth(width), gridHeight(height), title(wTitle),
      window(sf::VideoMode(sf::Vector2u(width * cSize, height * cSize)),
             title) {
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
}

void Graphic::display(std::unique_ptr<Grid> &grid) {
    window.setTitle(this->title);

    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (event->is<sf::Event::Resized>()) {
            windowResize(event->getIf<sf::Event::Resized>());
        }
    }

    window.clear(sf::Color(30, 30, 30));

    float offsetX, offsetY;
    float cellSizeDynamic = calculateCellSize(grid, offsetX, offsetY);
    drawGrid(grid, cellSizeDynamic, offsetX, offsetY);

    window.display();
}

void Graphic::editionMode(GameEngine *game, std::unique_ptr<Grid> &grid) {
    window.setTitle("Mode édition");
    bool saveCondition = false;

    while (window.isOpen()) {
        float offsetX, offsetY;
        float cellSizeDynamic = calculateCellSize(grid, offsetX, offsetY);

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::Resized>()) {
                windowResize(event->getIf<sf::Event::Resized>());
            }

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Escape) {
                    return;
                }

                if (key->code == sf::Keyboard::Key::Space) {
                    std::cout << "Démarrage de la simulation..." << std::endl;
                    game->startSimulation();
                    return;
                }

                if (key->code == sf::Keyboard::Key::Enter) {
                    if (saveCondition) {
                        if (!game->getFileManager().saveConfig(
                                game->getGrid())) {
                            return;
                        }

                        std::cout
                            << "Configuration sauvegardée dans le fichier: "
                            << game->getFileManager().getConfigName().filename()
                            << std::endl;
                        saveCondition = false;
                    } else {
                        saveCondition = true;
                        std::cout << "Appuyez de nouveau sur 'Entrée' pour "
                                     "sauvegarder la configuration"
                                  << std::endl;
                    }
                }
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                mouseClick(event->getIf<sf::Event::MouseButtonPressed>(), grid,
                           cellSizeDynamic, offsetX, offsetY);
            }
        }

        window.clear(sf::Color(30, 30, 30));
        drawGrid(grid, cellSizeDynamic, offsetX, offsetY);
        window.display();
    }
}

void Graphic::windowResize(const sf::Event::Resized *size) {
    sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f),
                              sf::Vector2f(static_cast<float>(size->size.x),
                                           static_cast<float>(size->size.y)));
    window.setView(sf::View(visibleArea));
}

float Graphic::calculateCellSize(const std::unique_ptr<Grid> &grid,
                                 float &offsetX, float &offsetY) const {
    float windowW = static_cast<float>(window.getSize().x);
    float windowH = static_cast<float>(window.getSize().y);
    float scaleX = windowW / static_cast<float>(grid->getWidth());
    float scaleY = windowH / static_cast<float>(grid->getHeight());
    float cellSizeDynamic = std::min(scaleX, scaleY);

    offsetX = (windowW - cellSizeDynamic * grid->getWidth()) / 2.f;
    offsetY = (windowH - cellSizeDynamic * grid->getHeight()) / 2.f;

    return cellSizeDynamic;
}

void Graphic::drawGrid(std::unique_ptr<Grid> &grid, float cellSizeDynamic,
                       float offsetX, float offsetY) {
    cell.setSize(sf::Vector2f(cellSizeDynamic - 1.f, cellSizeDynamic - 1.f));

    for (int x = 0; x < grid->getWidth(); ++x) {
        for (int y = 0; y < grid->getHeight(); ++y) {
            Cell *gridCell = grid->getCell(x, y);

            if (gridCell->getState() == CellState::ALIVE) {
                cell.setFillColor(sf::Color::White);
                cell.setOutlineThickness(0.f);
            } else {
                cell.setFillColor(sf::Color::Transparent);
                cell.setOutlineColor(sf::Color(70, 70, 70));
                cell.setOutlineThickness(1.f);
            }

            if (!gridCell->isEditable()) {
                cell.setOutlineColor(sf::Color::Red);
                cell.setOutlineThickness(
                    gridCell->getState() == CellState::ALIVE ? 1.f : 2.f);
            }

            cell.setPosition(sf::Vector2f(offsetX + x * cellSizeDynamic,
                                          offsetY + y * cellSizeDynamic));

            window.draw(cell);
        }
    }
}

bool Graphic::mouseClick(const sf::Event::MouseButtonPressed *mouse,
                         const std::unique_ptr<Grid> &grid,
                         float cellSizeDynamic, float offsetX, float offsetY) {
    float mouseX = static_cast<float>(mouse->position.x);
    float mouseY = static_cast<float>(mouse->position.y);

    float gridX = mouseX - offsetX;
    float gridY = mouseY - offsetY;

    if (gridX >= 0 && gridY >= 0) {
        int cellX = static_cast<int>(gridX / cellSizeDynamic);
        int cellY = static_cast<int>(gridY / cellSizeDynamic);

        if (cellX >= 0 && cellX < grid->getWidth() && cellY >= 0 &&
            cellY < grid->getHeight()) {

            Cell *c = grid->getCell(cellX, cellY);

            if (mouse->button == sf::Mouse::Button::Right) {

                if (c->isEditable()) {
                    grid->setCellObject(
                        cellX, cellY,
                        std::make_unique<CellObstacle>(c->getState()));
                } else {
                    grid->setCellObject(
                        cellX, cellY,
                        std::make_unique<CellSimple>(c->getState()));
                };
            } else if (mouse->button == sf::Mouse::Button::Left) {
                if (c->isEditable()) {
                    if (c->getState() == CellState::ALIVE) {
                        c->setState(CellState::DEATH);
                    } else {
                        c->setState(CellState::ALIVE);
                    };
                };
            };
            return true;
        };
    };
    return false;
};
