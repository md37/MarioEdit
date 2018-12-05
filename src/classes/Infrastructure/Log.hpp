#pragma once

#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "classes/Infrastructure/Scale.hpp"

class Log {

public:

    static void line();
    static void out(std::string label);
    static void out(sf::Rect<float> rect, std::string label);
    static void out(std::unique_ptr<Scale> &scale, std::string label);

};
