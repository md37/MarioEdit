#pragma once

#include <memory>
#include "classes/System/Scale.hpp"
#include "classes/System/TileFactory.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene/Grid.hpp"
#include "classes/Editor/Scene/SceneGenerator.hpp"
#include "classes/Editor/Scene/Animation/SpecialBlockBlinkAnimation.hpp"

class Scene : public RescalableInterface, DrawableInterface {

public:

    explicit Scene(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Scale> scale);

    void rescale(sf::Vector2u windowSize) override;
    void startTasks();
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

private:

    std::shared_ptr<Scale> scale;
    std::shared_ptr<Grid> grid;
    std::shared_ptr<SceneGenerator> sceneGenerator;

    std::shared_ptr<SpecialBlockBlinkAnimation> blinkAnimation;

    void reScaleTiles();
    void reSnapTilesToGrid();
};
