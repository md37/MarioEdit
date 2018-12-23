#pragma once

#include <memory>
#include <optional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Scene/Highlight.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "GridSettings.hpp"

class Grid : public RescalableInterface, public DrawableInterface {

public:

    explicit Grid(GridSettings settings);

    void rescale(std::unique_ptr<Scale>& scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    sf::Uint32 getCols() const;
    sf::Vector2u getSize() const;

    void turnHighlightOn(sf::Vector2u size);
    void turnHighlightOff();
    bool hasIncompleteEnding() const;

    std::optional<Highlight>& getHighlight();

    sf::Vector2f getPointOnGrid(sf::Vector2f pointOnScreen) const;
    sf::Vector2f pointOnGridToPosition(sf::Vector2i pointOnGrid) const;
    sf::Vector2i positionToPointOnGrid(sf::Vector2f pointOnScreen) const;
    sf::Vector2f getCenter(sf::Vector2u pointOnGrid) const;

private:

    GridSettings settings;

    sf::Color lineColor = sf::Color(0, 0, 0, 50);

    std::optional<Highlight> highlight;

    void drawHorizontalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const;
    void drawVerticalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const;
};
