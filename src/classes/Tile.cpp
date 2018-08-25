#include "Tile.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/Cursor.hpp"
#include "classes/Tile/TileRegistry.hpp"

std::shared_ptr<sf::RenderWindow> Tile::window;

void Tile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    Tile::window = window;
}

Tile::Tile(sf::Sprite sprite, TileConfig config) {
    this->sprite = sprite;
    this->config = config;
    highlightTileAnimation = std::make_shared<HighlightTileAnimation>(this);
    undoHighlightTileAnimation = std::make_shared<UndoHighlightTileAnimation>(this);
}

void Tile::change(sf::Uint32 x, sf::Uint32 y) {
    sf::IntRect textureRect;
    textureRect.width = config.tileWidth;
    textureRect.height = config.tileHeight;

    textureRect.top = (y * (config.tileHeight+config.separatorY)) + config.offsetY;
    textureRect.left = (x * (config.tileWidth+config.separatorX)) + config.offsetX;
    sprite.setTextureRect(textureRect);
}

void Tile::setPosition(sf::Vector2f position) {
    this->position = position;
    sprite.setPosition(position);
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

void Tile::setGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}

void Tile::snapToGrid() {
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

void Tile::snapToGrid(sf::Vector2u gridPosition) {
    this->gridPosition = gridPosition;
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

sf::Vector2i Tile::getSize() {
    return sf::Vector2i(
        sprite.getTextureRect().width * sprite.getScale().x,
        sprite.getTextureRect().height * sprite.getScale().y
    );
}

void Tile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Tile::handleEvent(Tile::Event event) {
    if (eventCallbacks.find(event) == eventCallbacks.end()) {
        return;
    }
    eventCallbacks[event](this);
}

void Tile::setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback) {
    eventCallbacks[event] = callback;
}

bool Tile::isMouseOver() {
    return isMouseOverFlag;
}

bool Tile::isDragging() {
    return isDraggingFlag;
}

void Tile::highlight() {
    if (undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->stop();
    }
    if (!highlightTileAnimation->isRunning()) {
        highlightTileAnimation->run();
    }
}

void Tile::undoHighlight() {
    if (highlightTileAnimation->isRunning()) {
        highlightTileAnimation->stop();
    }
    if (!undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->run();
    }
}

void Tile::snapToWindowBound() {
    if (isOnTopLeftCorner()) {
        snapToTopLeftCorner();
    } else if (isOnBottomLeftCorner()) {
        snapToBottomLeftCorner();
    } else if (isOnBottomRightCorner()) {
        snapToBottomRightCorner();
    } else if (isOnTopRightCorner()) {
        snapToTopRightCorner();
    } else if (isOnLeftEdge()) {
        snapToLeftEdge();
    } else if (isOnRightEdge()) {
        snapToRightEdge();
    } else if (isOnTopEdge()) {
        snapToTopEdge();
    } else if (isOnBottomEdge()) {
        snapToBottomEdge();
    } else {
        snapToCenterPoint();
    }
}

bool Tile::isOnLeftEdge() {
    return gridPosition.x == 0;
}

bool Tile::isOnRightEdge() {
    if (grid->hasIncompleteEnding()) {
        return false;
    }
    return gridPosition.x == grid->getSize().x-1;
}

bool Tile::isOnTopEdge() {
    return gridPosition.y == grid->getSize().y-1;
}

bool Tile::isOnBottomEdge() {
    return gridPosition.y == 0;
}

bool Tile::isOnTopRightCorner() {
    return isOnTopEdge() && isOnRightEdge();
}

bool Tile::isOnBottomRightCorner() {
    return isOnBottomEdge() && isOnRightEdge();
}

bool Tile::isOnBottomLeftCorner() {
    return isOnBottomEdge() && isOnLeftEdge();
}

bool Tile::isOnTopLeftCorner() {
    return isOnTopEdge() && isOnLeftEdge();
}

void Tile::snapToTopLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::snapToBottomLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::snapToBottomRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::snapToTopRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::snapToCenterPoint() {
    auto center = grid->getCenter(gridPosition);

    auto newSpriteScale = scale*scalePromotion;
    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

    position.x = center.x-newWidth/2;
    position.y = center.y-newHeight/2;
    sprite.setPosition(position);
}

void Tile::snapToLeftEdge() {
    snapToCenterPoint();
    position.x = 0;
    sprite.setPosition(position);
}

void Tile::snapToRightEdge() {
    snapToCenterPoint();
    position.x = window->getSize().x-getSize().x;
    sprite.setPosition(position);
}

void Tile::snapToTopEdge() {
    snapToCenterPoint();
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::snapToBottomEdge() {
    snapToCenterPoint();
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::correctCorners() {
    auto width = getSize().x;
    auto height = getSize().y;

    auto posX = sprite.getPosition().x;
    if (posX < 0) {
        posX = 0;
    }

    auto posY = sprite.getPosition().y;
    if (posY < 0) {
        posY = 0;
    }

    auto windowWidth = Tile::window->getSize().x;
    if (posX+width > windowWidth) {
        posX = windowWidth-width;
    }

    auto windowHeight = Tile::window->getSize().y;
    if (posY+height > windowHeight) {
        posY = windowHeight-height;
    }

    position = sf::Vector2f(posX, posY);
    sprite.setPosition(position);
}

void Tile::rescale(float scale) {
    this->scale = sf::Vector2f(scale, scale);
    sprite.setScale(this->scale*scalePromotion);
}

void Tile::startDrag() {
    sprite.setColor(sf::Color(255, 255, 255, 180));

    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);
    
    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->highlightOn();
}

void Tile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void Tile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    dragOffset = {0, 0};

    snapToGrid(grid->getHighlightPlace());

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    sf::Vector2f tileSize(getSize());
    positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;

    setPosition(positionOnGrid);
    grid->highlightOff();

    correctCorners();
}
