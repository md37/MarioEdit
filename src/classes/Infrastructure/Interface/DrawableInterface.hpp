#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class DrawableInterface {

public:

    virtual void draw(std::shared_ptr<sf::RenderWindow> window) const=0;

};