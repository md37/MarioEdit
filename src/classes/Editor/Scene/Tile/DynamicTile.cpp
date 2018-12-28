#include "DynamicTile.hpp"

#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Infrastructure/Log.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, std::shared_ptr<Grid>& grid, TileConfig config) : GridTile(sprite, grid, config) {

}

void DynamicTile::rescale(std::unique_ptr<Scale> &newScale) {
    snapToCenterPoint();

    AbstractTile::rescale(newScale);
}
void DynamicTile::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(sprite);
}

bool DynamicTile::isMouseOver() const {
    return isMouseOverFlag;
}

void DynamicTile::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
    if (undoHighlightAnimation.use_count()) {
        undoHighlightAnimation->stop();
    }

    highlightAnimation = std::make_shared<HighlightAnimation>(this);
    animationPerformer->add(highlightAnimation);
}

void DynamicTile::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void DynamicTile::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
    isReturning = true;
    if (highlightAnimation.use_count()) {
        highlightAnimation->stop();
    }

    undoHighlightAnimation = std::make_shared<UndoHighlightAnimation>(this);
    animationPerformer->add(undoHighlightAnimation);
}

bool DynamicTile::isDragging() const {
    return isDraggingFlag;
}

void DynamicTile::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::out("Tile StartDrag");

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn(getSizeOnGrid());
    std::optional<Highlight>& highlight = grid->getHighlight();

    if (highlight.has_value()) {
        highlight->setPosition(cursorPosition);
    }

    isDraggingFlag = true;
}

void DynamicTile::drag(sf::Vector2f cursorPosition) {
    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        highlight->setPosition(cursorPosition);
        setPosition(sf::Vector2f(cursorPosition-dragOffset));
    }
}

void DynamicTile::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::out("Tile Drop");

    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        dragOffset = {0, 0};
        dropHighlightPlace = highlight->getPointOnGrid();
        snapToGrid(dropHighlightPlace);

        sf::Vector2f positionOnGrid = highlight->getPosition();
        sf::Vector2f tileSize(getSize());
        positionOnGrid -= (tileSize-(tileSize/getScalePromotion()))/2.0f;

        setPosition(positionOnGrid);

        grid->turnHighlightOff();

        recalculateCenter();
        correctCorners();
        isDraggingFlag = false;
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

    auto windowWidth = AbstractTile::window->getSize().x;
    if (posX+width > windowWidth) {
        posX = windowWidth-width;
    }

    auto windowHeight = AbstractTile::window->getSize().y;
    if (posY+height > windowHeight) {
        posY = windowHeight-height;
    }

    sprite.setPosition(sf::Vector2f(posX, posY));
}

sf::Vector2i DynamicTile::getDropHighlightPlace() const {
    return dropHighlightPlace;
}
