#include "StaticTile.hpp"

StaticTile::StaticTile(sf::Sprite sprite, std::unique_ptr<Grid>& grid, TileConfig config) : GridTile(sprite, grid, config) {

}

void StaticTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}
