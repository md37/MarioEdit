#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/System/TileFactory.hpp"
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/Editor/Scene/Grid.hpp"

class Figure : public
    DrawableInterface, LocatableInterface, GridableInterface, LocatableOnGridInterface,
    RescalableInterface, HoverableInterface, DraggableInterface {

public:

    Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position);

    void rescale(std::shared_ptr<Scale> scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void drawFrame(std::shared_ptr<sf::RenderWindow> window);

    sf::Vector2f getPosition() override;
    sf::Vector2u getSize() override;

    sf::Vector2i getPointOnGrid() override;
    sf::Vector2u getSizeOnGrid() override;

public:

    void setGrid(std::shared_ptr<Grid> grid) override;
    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

    bool isMouseOver() override;
    void mouseEnter(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseOver(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseLeave(std::shared_ptr<AnimationPerformer> animationPerformer) override;

    bool isDragging() override;
    void startDrag(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void drag() override;
    void drop(std::shared_ptr<AnimationPerformer> animationPerformer) override;

protected:

    std::vector<std::shared_ptr<StaticTile>> tiles;

private:

    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    bool isMouseOverFlag = false;
    bool isFrameCreated = false;

    sf::Vector2i position;
    sf::RectangleShape frame;

    bool isDraggingFlag = false;
    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2f dragOffsetForHighlight = {0.0f, 0.0f};

    void createFrame();

    std::shared_ptr<StaticTile> findMostLeftTile();
    std::shared_ptr<StaticTile> findMostRightTile();
    std::shared_ptr<StaticTile> findMostTopTile();
    std::shared_ptr<StaticTile> findMostBottomTile();

    void recalculateHighlightPosition();
    void calculateDragOffset();
    void moveTiles();

    void updateFramePosition();
    void recalculateFramePosition();
};
