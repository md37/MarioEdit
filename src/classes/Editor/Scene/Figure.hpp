#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/System/TileFactory.hpp"
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/Editor/Scene/Grid.hpp"

class Figure : public DrawableInterface, RescalableInterface, HoverableInterface, SizeableInterface {

public:

    Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position);

    void snapToGrid();

    void rescale(std::shared_ptr<Scale> scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    bool isMouseOver() override;
    void mouseEnter(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseOver(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseLeave(std::shared_ptr<AnimationPerformer> animationPerformer) override;

    sf::Vector2f getPosition() override;
    sf::Vector2u getSize() override;

protected:

    bool isMouseOverFlag = false;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    sf::Vector2i position;
    std::vector<std::shared_ptr<StaticTile>> tiles;

private:

    std::shared_ptr<StaticTile> findMostLeftTile();
    std::shared_ptr<StaticTile> findMostRightTile();
    std::shared_ptr<StaticTile> findMostTopTile();
    std::shared_ptr<StaticTile> findMostBottomTile();

};
