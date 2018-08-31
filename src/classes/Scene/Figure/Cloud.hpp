#pragma once

#include "classes/Scene/Figure.hpp"

class Cloud : public Figure {

public:

    Cloud(sf::Vector2i position, sf::Uint8 size);

    void createTiles() override;

private:

    sf::Uint8 size;

};
