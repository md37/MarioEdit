#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class Cloud : public Figure {

public:

    Cloud(std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid>& grid, sf::Uint8 size);

    void changeVariant(sf::Uint8 variant) override;

protected:

    void generate();

private:

    sf::Uint8 size;
};
