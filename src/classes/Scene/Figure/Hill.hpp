#pragma once

#include "classes/Scene/Figure.hpp"

class Hill : public Figure {

public:

    Hill(sf::Vector2i position, sf::Vector2u size);

    void createTiles() override;

private:

    sf::Vector2u size;

};
