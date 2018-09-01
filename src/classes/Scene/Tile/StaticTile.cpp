#include "StaticTile.hpp"

StaticTile::StaticTile(sf::Sprite sprite, TileConfig config) : GridTile(sprite, config) {

}

void StaticTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}
