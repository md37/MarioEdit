#pragma once

#include <SFML/Graphics/Rect.hpp>

class Log {

public:

    static void line();
    static void out(std::string label);
    static void out(sf::Rect<float> rect, std::string label);

};
