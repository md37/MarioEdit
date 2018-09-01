#pragma once

#include "classes/Scene/Figure.hpp"

class Cloud : public Figure {

public:

    Cloud(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size);

private:

    sf::Uint8 size;

};
