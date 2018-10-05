#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/System/Interface/DraggableInterface.hpp"
#include "classes/System/Interface/HoverableInterface.hpp"
#include "classes/System/TileFactory.hpp"
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

class TileFactory;

class ButtonTile : public Tile, public DrawableInterface, public DraggableInterface, public HoverableInterface {

public:

    explicit ButtonTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void mouseEnter(AnimationPerformer& animationPerformer) override;
    void mouseOver(AnimationPerformer& animationPerformer) override;
    void mouseLeave(AnimationPerformer& animationPerformer) override;
    bool isMouseOver() override;

    void startDrag(AnimationPerformer& animationPerformer) override;
    void drag() override;
    void drop(AnimationPerformer& animationPerformer) override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    std::shared_ptr<DynamicTile> cloneToDynamicTile(std::shared_ptr<TileFactory> tileFactory);

private:

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

};
