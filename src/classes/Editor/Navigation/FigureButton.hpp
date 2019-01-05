#pragma once

#include "classes/Editor/Object/FigureGenerator/AbstractFigureGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/BushGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/CloudGenerator.hpp"
#include "classes/Editor/Object/FigureGenerator/HillGenerator.hpp"
#include "classes/Editor/Object/StaticFigure.hpp"
#include "classes/Editor/Navigation/AbstractButton.hpp"

class FigureButton : public StaticFigure, AbstractButton {

public:

    FigureButton(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, std::shared_ptr<AbstractFigureGenerator> generator
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

private:

    std::shared_ptr<AbstractFigureGenerator> generator;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

};
