#pragma once

#include <map>
#include <optional>
#include <SFML/Window/Keyboard.hpp>

class Keyboard {

public:

    void press(sf::Keyboard::Key key);
    void release(sf::Keyboard::Key key);

    bool isPressed(sf::Keyboard::Key key);
    bool isNumericKeyPressed();

    std::optional<sf::Uint8> getPressedNumeric();

private:

    std::map<sf::Keyboard::Key, bool> keys;

};