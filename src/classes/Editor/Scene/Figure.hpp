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

    Figure(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid);

    void rescale(std::unique_ptr<Scale> &scale) override;
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
    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() override;
    void startDrag(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag() override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

protected:

    std::vector<std::shared_ptr<StaticTile>> tiles;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2i pointOnGrid = {0, 0};

private:

    std::unique_ptr<TileFactory> &tileFactory;
    std::shared_ptr<Grid> grid;

    bool isMouseOverFlag = false;
    bool isFrameCreated = false;

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
