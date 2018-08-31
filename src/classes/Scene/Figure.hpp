#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class Figure {

public:

    Figure(sf::Vector2i position);

    virtual void createTiles()=0;

protected:

    sf::Vector2i position;

};
