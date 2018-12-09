#include "Keyboard.hpp"

void Keyboard::press(sf::Keyboard::Key key) {
    keys[key] = true;
}

void Keyboard::release(sf::Keyboard::Key key) {
    keys[key] = false;
}

bool Keyboard::isPressed(sf::Keyboard::Key key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
       return it->second;
    }
    return false;
}

bool Keyboard::isNumericKeyPressed() const {
    return isPressed(sf::Keyboard::Key::Num0) || isPressed(sf::Keyboard::Key::Num1) ||
           isPressed(sf::Keyboard::Key::Num2) || isPressed(sf::Keyboard::Key::Num3) ||
           isPressed(sf::Keyboard::Key::Num4) || isPressed(sf::Keyboard::Key::Num5) ||
           isPressed(sf::Keyboard::Key::Num6) || isPressed(sf::Keyboard::Key::Num7) ||
           isPressed(sf::Keyboard::Key::Num8) || isPressed(sf::Keyboard::Key::Num9);
}

std::optional<sf::Uint8> Keyboard::getPressedNumeric() const {
    for (auto key: keys) {
        if (!key.second) {
            continue;
        }

        if (key.first >= sf::Keyboard::Key::Num0 && key.first <= sf::Keyboard::Key::Num9) {
            return key.first-sf::Keyboard::Key::Num0;
        }
    }
    return {};
}
