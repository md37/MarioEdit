#include "TileNavigation.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

TileNavigation::TileNavigation(std::unique_ptr<TileFactory> &tileFactory) : tileFactory(tileFactory) {
    generateBox();
    generateTileButtons();
}

void TileNavigation::generateBox() {
    auto newPosition = box.getPosition();
    box.setPosition(newPosition);

    sf::Color bgColor(188, 211, 254);
    box.setFillColor(bgColor);

    sf::Color borderColor(255, 255, 255);
    box.setOutlineColor(borderColor);
}

void TileNavigation::generateTileButtons() {
    auto ground = tileFactory->createButtonTile(0, 0);
    ground->setPosition(sf::Vector2f(20, 20));

    auto brick = tileFactory->createButtonTile(5, 0);
    brick->setPosition(sf::Vector2f(120, 20));

    auto stair = tileFactory->createButtonTile(2, 2);
    stair->setPosition(sf::Vector2f(220, 20));

    auto questionMark = tileFactory->createButtonTile(0, 11);
    questionMark->setPosition(sf::Vector2f(320, 20));
}

void TileNavigation::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(box);
    drawTileButtons(window);
}

void TileNavigation::drawTileButtons(std::shared_ptr<sf::RenderWindow> &window) const {
    auto buttonTiles = ObjectRegistry::getButtonTiles();
    for (auto const &tile : buttonTiles) {
        tile->draw(window);
    }
}

void TileNavigation::rescale(std::unique_ptr<Scale> &scale) {
    auto boxSize = box.getSize();
    if (boxSize.x == 0) {
        boxSize = sf::Vector2f(boxWidth, boxHeight);
    }
    boxSize *= scale->getRatio();
    box.setSize(boxSize);

    auto buttonTiles = ObjectRegistry::getButtonTiles();
    for (auto const &tile : buttonTiles) {
        tile->rescale(scale);
    }
}
