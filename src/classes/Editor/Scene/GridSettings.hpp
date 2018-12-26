#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Scale.hpp"

class GridSettings : public RescalableInterface {

public:

    static const sf::Uint32 Auto = 0;

    GridSettings(sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f size);

    sf::Uint32 getRows() const;
    sf::Uint32 getCols() const;
    sf::Vector2f getSize() const;

    void rescale(std::unique_ptr<Scale> &scale) override;

    sf::Uint32 getLineThickness() const;
    float getLineDistance() const;
    bool hasIncompleteEnding() const;

private:

    sf::Uint32 rows;
    sf::Uint32 rowsOrig;
    sf::Uint32 cols;
    sf::Uint32 colsOrig;
    sf::Vector2f size;
    sf::Vector2f sizeOrig;

    float lineDistance;
    sf::Uint32 lineThickness;
    sf::Uint32 lineThicknessDivider = 400;
    bool hasIncompleteEndingFlag = false;

    void resolveAutoSize(const std::unique_ptr<Scale> &scale);
};
