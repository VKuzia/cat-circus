#include "audio.h"

Audio::Audio() {
    music_player_ = new QMediaPlayer(nullptr);
    sound_player_ = new QMediaPlayer(nullptr);
}

void Audio::PlayMusic() {
    music_player_->setMedia(QUrl::fromLocalFile(
                                kPathToAudio + "music/menu_music.wav"));
    music_player_->play();
}

void Audio::PlaySound() {
    sound_player_->setMedia(QUrl::fromLocalFile(
                                kPathToAudio + "sound/life_lose.mp3"));
//    music_player_->setMedia(QUrl::fromLocalFile("E:/qt_projects/audio/data/audio/music/menu_music.wav")); sound/life_lose.mp3
    sound_player_->play();
}

void Audio::SwitchMusic() {

}

void Audio::SwitchSound() {

}

void Audio::SetVolume() {

}

void Audio::Stop() {

}

void Audio::Finish() {

}



