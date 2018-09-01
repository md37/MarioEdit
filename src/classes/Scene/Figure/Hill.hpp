#pragma once

#include "classes/Scene/Figure.hpp"

class Hill : public Figure {

public:

    Hill(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Vector2u size);

    void createTiles() override;

private:

    sf::Vector2u size;

};
