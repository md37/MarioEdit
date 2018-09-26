#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class Hill : public Figure {

public:

    Hill(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size);

private:

    sf::Uint8 size;

};
