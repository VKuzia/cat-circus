#include "game.h"

Game::Game() : window_(nullptr) {}

void Game::Start() {
    window_.SetUp();
    window_.show();
}
