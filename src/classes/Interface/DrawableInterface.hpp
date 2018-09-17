#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class DrawableInterface {

public:

    virtual void draw(std::shared_ptr<sf::RenderWindow> window)=0;

};