#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Infrastructure/Collision.hpp"
#include "classes/Infrastructure/TileFactory.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Editor/Scene/Grid.hpp"

class Figure : public
    DrawableInterface, SquareableInterface, GridableInterface, SquareableOnGridInterface,
    RescalableInterface, HoverableInterface, DraggableInterface {

public:

    Figure(std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid> &grid);

    void rescale(std::unique_ptr<Scale> &scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void drawFrame(std::shared_ptr<sf::RenderWindow> window);

    sf::Vector2f getPosition() override;
    sf::Vector2u getSize() override;

    sf::Vector2i getPointOnGrid() override;
    sf::Vector2u getSizeOnGrid() override;

    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

    bool isMouseOver() override;
    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() override;
    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    virtual void changeVariant(sf::Uint8 variant)=0;

protected:

    std::unique_ptr<TileFactory> &tileFactory;
    std::unique_ptr<Grid>& grid;

    std::vector<std::shared_ptr<StaticTile>> tiles;
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2i pointOnGrid = {0, 0};

    sf::RectangleShape frame;

    void resetFrame();

private:

    bool isMouseOverFlag = false;
    bool isFrameCreated = false;

    bool isDraggingFlag = false;
    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2f dragOffsetForHighlight = {0.0f, 0.0f};

    sf::Color frameColorNormal = sf::Color(255, 255, 255, 30);
    sf::Color frameColorError = sf::Color(255, 0, 0, 100);

    std::shared_ptr<StaticTile> findMostLeftTile();
    std::shared_ptr<StaticTile> findMostRightTile();
    std::shared_ptr<StaticTile> findMostTopTile();
    std::shared_ptr<StaticTile> findMostBottomTile();

    void recalculateHighlightPosition(sf::Vector2f cursorPosition);
    void calculateDragOffset(sf::Vector2f cursorPosition);
    void moveTiles(sf::Vector2f prevPosition);

    void updateFramePosition();
    void recalculateFramePosition(sf::Vector2f cursorPosition);

    sf::Rect<float> getRect();

    bool checkForCollisions();
};
