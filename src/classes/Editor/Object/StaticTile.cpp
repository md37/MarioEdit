#include "StaticTile.hpp"

StaticTile::StaticTile(sf::Sprite sprite, std::shared_ptr<Grid> grid, TileConfig config) : GridTile(sprite, grid, config) {

}

void StaticTile::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(sprite);
}
