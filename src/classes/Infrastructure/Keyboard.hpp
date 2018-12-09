#pragma once

#include <map>
#include <optional>
#include <SFML/Window/Keyboard.hpp>

class Keyboard {

public:

    void press(sf::Keyboard::Key key);
    void release(sf::Keyboard::Key key);

    bool isPressed(sf::Keyboard::Key key) const;
    bool isNumericKeyPressed() const;

    std::optional<sf::Uint8> getPressedNumeric() const;

private:

    std::map<sf::Keyboard::Key, bool> keys;

};