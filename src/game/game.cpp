#include "game.h"

Game::Game() : window_(width_, height_, nullptr) {}

void Game::Start() { window_.show(); }
