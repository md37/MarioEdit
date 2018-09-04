#pragma once

#include <memory>
#include "classes/Scene/Grid.hpp"
#include "classes/Scene/SceneGenerator.hpp"
#include "classes/Scene/TileBar.hpp"
#include "classes/Scene/Tile/TileFactory.hpp"
#include "classes/Scene/Scale.hpp"
#include "classes/Animation/FrameAnimation/Animation/SpecialBlockBlinkingAnimation.hpp"

class Scene {

public:

    explicit Scene(std::shared_ptr<sf::RenderWindow> window);

    std::shared_ptr<Scale> getScale();

    void rescale();
    void runTasks();
    void draw();

private:

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<TileBar> tileBar;
    std::shared_ptr<Scale> scale;
    std::shared_ptr<Grid> grid;
    std::shared_ptr<SceneGenerator> sceneGenerator;

    std::shared_ptr<SpecialBlockBlinkingAnimation> blinkAnimation;

    void reScaleTiles();
    void reSnapTilesToGrid();
};
