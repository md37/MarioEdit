#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class Bush : public Figure {

public:

    Bush(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size);

private:

    sf::Uint8 size;

};
