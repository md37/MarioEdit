#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Infrastructure/TileConfig.hpp"
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Infrastructure/Interface/SquareableInterface.hpp"

class AbstractTile : public SquareableInterface, RescalableInterface {

public:

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    explicit AbstractTile(sf::Sprite sprite, TileConfig config=TileConfig());

    sf::Vector2f positionPromotion = {0.0f, 0.0f};

    void changeImage(sf::Uint32 x, sf::Uint32 y);
    void rescale(std::unique_ptr<Scale> &newScale) override;

    void setScalePromotion(float scalePromotion);
    float getScalePromotion() const;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const override;
    sf::Vector2u getSize() const override;

    void snapToCenterPoint();

    bool isTypeOf(std::shared_ptr<AbstractTile> tile) const;

protected:

    static std::shared_ptr<sf::RenderWindow> window;

    sf::Sprite sprite;
    sf::Vector2f centerPoint;

    sf::Vector2u imagePosition;

    void recalculateCenter();

private:

    sf::Vector2f scale = {1.0f, 1.0f};
    float scalePromotion = 1.0f;
    TileConfig config;

};
