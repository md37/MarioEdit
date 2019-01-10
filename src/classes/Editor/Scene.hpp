#pragma once

#include <memory>
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"
#include "classes/Editor/Navigation/AbstractNavigation.hpp"
#include "classes/Editor/Scene/Grid/Grid.hpp"
#include "classes/Editor/Scene/Animation/SpecialBlockBlinkAnimation.hpp"
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Infrastructure/TileFactory.hpp"

class Scene : public RescalableInterface, DrawableInterface {

public:

    explicit Scene(std::unique_ptr<TileFactory> &tileFactory);

    void rescale(std::unique_ptr<Scale> &scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    std::shared_ptr<Grid> getGrid();
    std::shared_ptr<DynamicTile> getDraggingTile() const;
    std::shared_ptr<DynamicFigure> getDraggingFigure() const;

private:

    std::shared_ptr<Grid> grid;

    void reScaleTiles(std::unique_ptr<Scale> &scale);
    void reSnapTilesToGrid();
};
