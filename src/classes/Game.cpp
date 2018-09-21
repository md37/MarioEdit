#include "Game.hpp"

void Game::start() {
    isStartedFlag = true;
}

bool Game::isStarted() {
    return isStartedFlag;
}

void Game::handleEvents(Keyboard& keyboard, Cursor& cursor) {

}
