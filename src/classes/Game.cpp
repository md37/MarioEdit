#include "Game.hpp"

void Game::start() {
    isStartedFlag = true;
}

bool Game::isStarted() const {
    return isStartedFlag;
}

void Game::handleEvents(Keyboard& keyboard, Cursor& cursor) {

}
