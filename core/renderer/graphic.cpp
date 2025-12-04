#include "graphic.hpp"
#include "../core/gameEngine.hpp"

void Graphic::editionMode(GameEngine *game, std::unique_ptr<Grid> &grid) {
    window.setTitle("Mode édition");
    bool saveCondition = false;

    while (window.isOpen()) {
        float offsetX, offsetY;
        float cellSizeDynamic = calculateCellSize(grid, offsetX, offsetY);

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            };

            if (event->is<sf::Event::Resized>()) {
                windowResize(event->getIf<sf::Event::Resized>());
            };

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Escape) {
                    return;
                };

                if (key->code == sf::Keyboard::Key::Space) {
                    game->startSimulation();
                    return;
                };

                if (key->code == sf::Keyboard::Key::Enter) {
                    if (saveCondition) {
                        if (!game->getFileManager().saveConfig(
                                game->getGrid())) {
                            return;
                        };

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
                    };
                };
            };

            if (event->is<sf::Event::MouseButtonPressed>()) {
                mouseClick(event->getIf<sf::Event::MouseButtonPressed>(), grid,
                           cellSizeDynamic, offsetX, offsetY);
            };
        };

        window.clear(sf::Color(30, 30, 30));
        drawGrid(grid, cellSizeDynamic, offsetX, offsetY);
        window.display();
    };
};