#pragma once

#include <memory>
#include "classes/Scene/Tile/TileFactory.hpp"
#include "classes/Scene/Grid.hpp"

class SceneGenerator {

public:

    SceneGenerator(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid);
    void generate();

private:

    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    void generateBackground();
    void createBushes();
    void createClouds();
    void createHills();

    void generateForeground();

};
