#include "Navigation.hpp"

#include <SFML/Graphics/Text.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

Navigation::Navigation(std::shared_ptr<TileFactory> tileFactory) {
    this->tileFactory = tileFactory;

    generateBox();
    generateTileButtons();
}

void Navigation::rescale(std::shared_ptr<Scale> scale) {
    boxHeight = 120* scale->getRatio();

    auto windowSize = scale->getWindowSize();
    sf::Vector2f size(windowSize);
    size.y = boxHeight;
    box.setSize(size);

    auto buttonTiles = ObjectRegistry::getButtonTiles();
    for (auto const &tile : buttonTiles) {
        tile->rescale(scale);
    }
}

void Navigation::generateBox() {
    auto newPosition = box.getPosition();
    box.setPosition(newPosition);

    sf::Color bgColor(188, 211, 254);
    box.setFillColor(bgColor);

    sf::Color borderColor(255, 255, 255);
    box.setOutlineColor(borderColor);
}

void Navigation::generateTileButtons() {
    auto ground = tileFactory->createButtonTile(0, 0);
    ground->setPosition(sf::Vector2f(20, 20));
    ground->setBorder(1);

    auto brick = tileFactory->createButtonTile(5, 0);
    brick->setPosition(sf::Vector2f(120, 20));
    brick->setBorder(1);

    auto stair = tileFactory->createButtonTile(2, 2);
    stair->setPosition(sf::Vector2f(220, 20));
    stair->setBorder(1);

    auto questionMark = tileFactory->createButtonTile(0, 11);
    questionMark->setPosition(sf::Vector2f(320, 20));
    questionMark->setBorder(1);
}

void Navigation::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(box);
    drawTileButtons(window);
}

void Navigation::drawTileButtons(std::shared_ptr<sf::RenderWindow> &window) const {
    auto buttonTiles = ObjectRegistry::getButtonTiles();
    for (auto const &tile : buttonTiles) {
        tile->draw(window);
    }
}
