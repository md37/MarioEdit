#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Scene/Grid/Grid.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/TileFactory.hpp"

class Figure: public DrawableInterface, SquareableInterface, GridableInterface, SquareableOnGridInterface, RescalableInterface {

public:

    explicit Figure(std::unique_ptr<TileFactory> &tileFactory);

    void rescale(std::unique_ptr<Scale> &scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    sf::Vector2f getPosition() const override;
    sf::Vector2u getSize() const override;

    sf::Vector2i getPointOnGrid() const override;
    sf::Vector2u getSizeOnGrid() const override;

    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

protected:

    std::unique_ptr<TileFactory> &tileFactory;
    std::shared_ptr<Grid> grid;

    std::vector<std::shared_ptr<StaticTile>> tiles;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2i pointOnGrid = {0, 0};

    sf::Rect<float> getRect() const;

private:

    std::shared_ptr<StaticTile> findMostLeftTile() const;
    std::shared_ptr<StaticTile> findMostRightTile() const;
    std::shared_ptr<StaticTile> findMostTopTile() const;
    std::shared_ptr<StaticTile> findMostBottomTile() const;

};
