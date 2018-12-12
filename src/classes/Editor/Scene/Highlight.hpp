#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/SquareableInterface.hpp"
#include "classes/Infrastructure/Interface/SquareableOnGridInterface.hpp"

class Highlight : DrawableInterface, SquareableInterface, SquareableOnGridInterface {

public:

    explicit Highlight(sf::Color color, float lineDistance);

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const override;

    void setSize(sf::Vector2u size);
    sf::Vector2u getSize() const override;

    sf::Vector2i getPointOnGrid() const override;
    sf::Vector2u getSizeOnGrid() const override;

    void setLineDistance(float lineDistance);

private:

    sf::RectangleShape area;
    sf::Vector2u size;
    float lineDistance;

    void recalculateSize();
};
