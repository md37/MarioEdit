#include "World.hpp"


World::World(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, std::shared_ptr<TileSet> tileSet) {
    this->window = window;
    this->grid = grid;
    this->tileSet = tileSet;
}