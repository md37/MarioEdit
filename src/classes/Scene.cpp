#include "Scene.hpp"

#include "defines.hpp"
#include "classes/Scale.hpp"
#include "classes/Tile/TileRegistry.hpp"

Scene::Scene(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;
    grid = std::make_shared<Grid>(window->getSize());
    tileFactory = std::make_shared<TileFactory>("resources/tiles2.png");

    generateScene();

    blinkAnimation = std::make_shared<SpecialBlockBlinkingAnimation>();
}

void Scene::generateScene() {
    auto questionMark = tileFactory->createDynamicTile(0, 5);
    questionMark->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->mouseEnter();
    });
    questionMark->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->mouseLeave();
    });
    questionMark->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->changeImage(0, 5);
        tile->startDrag();
    });
    questionMark->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    questionMark->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(2, 1));
}

void Scene::runTasks() {
    blinkAnimation->run();
}

void Scene::rescale() {
    Scale::rescale(window->getSize());
    Tile::setWindow(window);
    grid->rescale(window->getSize());
    reSnapTilesToGrid();
}

void Scene::reSnapTilesToGrid() {
    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (size_t i=0; i < dynamicTiles.size(); i++) {
        auto tile = dynamicTiles[i];
        tile->snapToGrid();
    }
}

void Scene::draw() {
    window->clear(BG_LIGHT_COLOR);
    grid->draw(window);

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (std::size_t i=0; i<dynamicTiles.size(); i++) {
        dynamicTiles[i]->draw(window);
    }
}
