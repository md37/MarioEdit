#pragma once

#include "classes/Tile.hpp"
#include "classes/Interface/DrawableInterface.hpp"
#include "classes/Interface/DraggableInterface.hpp"
#include "classes/Interface/HoverableInterface.hpp"

class ButtonTile : public Tile, public DrawableInterface, public DraggableInterface, public HoverableInterface {

public:

    ButtonTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void mouseEnter() override;
    void mouseLeave() override;

    void startDrag() override;
    void drag() override;
    void drop() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

};
