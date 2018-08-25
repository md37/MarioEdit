#pragma once

#include <memory>
#include "classes/Tile/TileFactory.hpp"
#include "classes/Grid.hpp"
#include "classes/Animation/FrameAnimation/Animation/SpecialBlockBlinkingAnimation.hpp"

class Scene {

public:

    Scene(std::shared_ptr<sf::RenderWindow> window);

    void rescale();
    void runTasks();
    void draw();

private:

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    std::shared_ptr<SpecialBlockBlinkingAnimation> blinkAnimation;

    void reSnapTilesToGrid();

    void generateScene() const;
};
