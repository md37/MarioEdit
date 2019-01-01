#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Editor/Object/AbstractTile.hpp"
#include "classes/Editor/Navigation/AbstractButton.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/TileFactory.hpp"

class TileFactory;

class TileButton : public AbstractTile, AbstractButton {

public:

    explicit TileButton(sf::Sprite sprite, TileConfig config=TileConfig());

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isMouseOver() const override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isDragging() const override;

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    std::shared_ptr<DynamicTile> cloneToDynamicTile(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> &grid
    );

private:

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

};
