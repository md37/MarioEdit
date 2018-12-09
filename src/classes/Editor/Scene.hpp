#pragma once

#include <memory>
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Infrastructure/TileFactory.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene/Grid.hpp"
#include "classes/Editor/Scene/SceneGenerator.hpp"
#include "classes/Editor/Scene/Animation/SpecialBlockBlinkAnimation.hpp"

class Scene : public RescalableInterface, DrawableInterface {

public:

    explicit Scene(std::unique_ptr<TileFactory> &tileFactory);

    void rescale(std::unique_ptr<Scale> &scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    std::unique_ptr<Grid>& getGrid();
    std::shared_ptr<DynamicTile> getDraggingTile() const;

private:

    std::unique_ptr<Grid> grid;
    std::unique_ptr<SceneGenerator> sceneGenerator;

    void reScaleTiles(std::unique_ptr<Scale> &scale);
    void reSnapTilesToGrid();
};
