#include "Tilebar.hpp"

#include <SFML/Graphics/Text.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

Tilebar::Tilebar(std::shared_ptr<TileFactory> tileFactory) {
    this->tileFactory = tileFactory;

    generateBox();
    generateDynamicTileButtons();
}

void Tilebar::rescale(sf::Vector2u windowSize) {
    boxHeight = windowSize.y*0.155;

    sf::Vector2f size(windowSize);
    size.y = boxHeight;
    box.setSize(size);

    float lineThickness = windowSize.y / lineThicknessDivider;
    box.setOutlineThickness(lineThickness);
}

void Tilebar::generateBox() {
    auto newPosition = box.getPosition();
    box.setPosition(newPosition);

    sf::Color bgColor(188, 211, 254);
    box.setFillColor(bgColor);

    sf::Color borderColor(0, 0, 0);
    box.setOutlineColor(borderColor);
}

void Tilebar::generateDynamicTileButtons() {
    auto ground = tileFactory->createButtonTile(0, 0);
    ground->setPosition(sf::Vector2f(100, 100));

    auto brick = tileFactory->createButtonTile(5, 0);
    brick->setPosition(sf::Vector2f(300, 100));

    auto stair = tileFactory->createButtonTile(2, 2);
    stair->setPosition(sf::Vector2f(500, 100));

    auto questionMark = tileFactory->createButtonTile(0, 11);
    questionMark->setPosition(sf::Vector2f(700, 100));
}

void Tilebar::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(box);
    drawDynamicTileButtons(window);
}

void Tilebar::drawDynamicTileButtons(std::shared_ptr<sf::RenderWindow> &window) const {
    auto buttonTiles = ObjectRegistry::getButtonTiles();
    for (auto const &tile : buttonTiles) {
        tile->draw(window);
    }
}
