#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Scale.hpp"

class Settings : public RescalableInterface {

public:

    static const sf::Uint32 Auto = 0;

    Settings(sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f position, sf::Vector2f size);
    explicit Settings(float scale, sf::Vector2f position=sf::Vector2f(0, 0));

    sf::Uint32 getRows() const;
    sf::Uint32 getCols() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    float getScale() const;

    void rescale(std::unique_ptr<Scale> &scale) override;

    sf::Uint32 getLineThickness() const;
    float getLineDistance() const;
    bool hasIncompleteEnding() const;

private:

    float scale = 1.0f;
    sf::Uint32 rows;
    sf::Uint32 rowsOrig;
    sf::Uint32 cols;
    sf::Uint32 colsOrig;
    sf::Vector2f size;
    sf::Vector2f sizeOrig;
    sf::Vector2f position;

    float lineDistance;
    sf::Uint32 lineThickness;
    sf::Uint32 lineThicknessDivider = 400;
    bool hasIncompleteEndingFlag = false;

    void resolveAutoSize(const std::unique_ptr<Scale> &scale);
};
