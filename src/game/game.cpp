#include "game.h"

Game::Game(InfoManager* info) : info_(info), window_(info, nullptr) {}

void Game::Start() { window_.show(); }
