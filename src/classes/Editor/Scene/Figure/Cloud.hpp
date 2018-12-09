#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class Cloud : public Figure {

public:

    Cloud(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);

protected:

    void generate(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> &grid, sf::Uint8 size);

private:

    sf::Uint8 size;
};
