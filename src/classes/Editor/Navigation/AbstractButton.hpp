#pragma once

#include "classes/Infrastructure/Interface/DraggableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"

class AbstractButton : public DrawableInterface, DraggableInterface, HoverableInterface {

protected:

    sf::RectangleShape background;
    sf::Uint8 borderSize = 1;

};