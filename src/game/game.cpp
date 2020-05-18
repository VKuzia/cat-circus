#include "game.h"

#include "src/menu/audio.h"

Game::Game() : window_(nullptr) {}

void Game::Start() {
  window_.SetUp();
  window_.show();

  Audio::PlayMenuMusic();
}
