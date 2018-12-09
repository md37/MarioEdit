#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/TileFactory.hpp"
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

class TileFactory;

class ButtonTile : public Tile, public DrawableInterface, public DraggableInterface, public HoverableInterface {

public:

    explicit ButtonTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isMouseOver() override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    std::shared_ptr<DynamicTile> cloneToDynamicTile(
        std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid> &grid
    );

private:

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

};
