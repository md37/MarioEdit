#include "DynamicTile.hpp"

#include "classes/Cursor.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, TileConfig config) : GridTile(sprite, config) {
    highlightTileAnimation = std::make_shared<HighlightTileAnimation>(this);
    undoHighlightTileAnimation = std::make_shared<UndoHighlightTileAnimation>(this);
}

void DynamicTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void DynamicTile::handleEvent(DynamicTile::Event event) {
    if (eventCallbacks.find(event) == eventCallbacks.end()) {
        return;
    }
    eventCallbacks[event](this);
}

void DynamicTile::addEventHandler(DynamicTile::Event event, std::function<void(DynamicTile *tile)> callback) {
    eventCallbacks[event] = callback;
}

void DynamicTile::startDrag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn();
    isDraggingFlag = true;
}

void DynamicTile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void DynamicTile::drop() {
    dragOffset = {0, 0};

    snapToGrid(grid->getHighlightPlace());

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    sf::Vector2f tileSize(getSize());
    positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;

    setPosition(positionOnGrid);
    grid->turnHighlightOff();

    correctCorners();
    isDraggingFlag = false;
}

bool DynamicTile::isMouseOver() {
    return isMouseOverFlag;
}

bool DynamicTile::isDragging() {
    return isDraggingFlag;
}

void DynamicTile::mouseEnter() {
    isMouseOverFlag = true;
    if (undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->stop();
    }
    if (!highlightTileAnimation->isRunning()) {
        highlightTileAnimation->run();
    }
}

void DynamicTile::mouseLeave() {
    isMouseOverFlag = false;
    if (highlightTileAnimation->isRunning()) {
        highlightTileAnimation->stop();
    }
    if (!undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->run();
    }
}

void DynamicTile::correctCorners() {
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
