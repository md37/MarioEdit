#pragma once

#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

class Bush : public DynamicFigure {

public:

    Bush(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);
    Bush(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size);

    void changeVariant(sf::Uint8 variant) override;

private:

    sf::Uint8 size;

    void generate();

};
