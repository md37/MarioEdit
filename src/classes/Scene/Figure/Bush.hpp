#pragma once

#include "classes/Scene/Figure.hpp"

class Bush : public Figure {

public:

    Bush(sf::Vector2i position, sf::Uint8 size);

    void createTiles() override;

private:

    sf::Uint8 size;

};
