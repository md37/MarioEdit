#pragma once

#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Animation/AnimationPerformer.hpp"

class DraggableInterface {

public:

    virtual void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer)=0;
    virtual void drag(sf::Vector2f cursorPosition)=0;
    virtual void drop(std::unique_ptr<AnimationPerformer> &animationPerformer)=0;

    virtual bool isDragging() const=0;

};
