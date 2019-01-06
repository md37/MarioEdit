#pragma once

#include "classes/Editor/Object/FigureGenerator/AbstractFigureGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/BushGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/CloudGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/HillGenerator.hpp"
#include "classes/Editor/Object/StaticFigure.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"
#include "classes/Editor/Navigation/AbstractButton.hpp"

class FigureButton : public StaticFigure, AbstractButton {

public:

    FigureButton(
        sf::Vector2f position,
        std::unique_ptr<TileFactory> &tileFactory,
        std::shared_ptr<Grid> grid,
        std::shared_ptr<AbstractFigureGenerator> generator,
        sf::Vector2i pointOnGrid=sf::Vector2i(0, 0)
    );

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;
    void rescale(std::unique_ptr<Scale> &newScale) override;

    bool isMouseOver() const override;

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() const override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    void cutBorder(float top, float left, float bottom, float right);

    sf::Vector2f getPosition() const override;
    sf::Vector2u getSize() const override;

    std::shared_ptr<DynamicFigure> cloneToDynamicFigure(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid
    );

private:

    std::shared_ptr<AbstractFigureGenerator> generator;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    sf::Color backgroundColor = sf::Color(255, 255, 255, 120);

    float borderCutTop = 0;
    float borderCutLeft = 0;
    float borderCutBottom = 0;
    float borderCutRight = 0;

    void rescaleTiles(std::unique_ptr<Scale> &newScale);
    void rescaleBackground(const std::unique_ptr<Scale> &newScale);
};
