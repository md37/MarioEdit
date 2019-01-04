#pragma once

#include <memory>
#include "classes/Infrastructure/TileFactory.hpp"
#include "classes/Editor/Scene/Grid/Grid.hpp"

class SceneGenerator {

public:

    SceneGenerator(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid);
    void generate();

private:

    std::unique_ptr<TileFactory> &tileFactory;
    std::shared_ptr<Grid> grid;

    void generateBackground();
    void createBushes();
    void createClouds();
    void createHills();

};
