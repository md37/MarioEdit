#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class Bush : public Figure {

public:

    Bush(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);

    void changeVariant(sf::Uint8 variant) override;

private:

    sf::Uint8 size;

    void generate();

};
