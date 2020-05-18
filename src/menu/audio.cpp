#include "audio.h"

QString Audio::kPathToAudio_ = QDir::currentPath() + "/data/audio/";
QMediaPlayer Audio::music_player_;
QMediaPlayer Audio::sound_player_;
bool Audio::unmuted_ = true;

QMediaPlaylist Audio::menu_songs_;
QMediaPlaylist Audio::game_songs_;

Audio::Audio() {}

void Audio::PlayMenuMusic() {
    if (unmuted_) {
        music_player_.stop();
        music_player_.setPlaylist(&menu_songs_);
        music_player_.play();
    }
}

void Audio::PlayGameMusic() {
    if (unmuted_) {
        music_player_.stop();
        music_player_.setPlaylist(&game_songs_);
        music_player_.play();
    }
}

void Audio::PlayMusic(QString content) {
    if (unmuted_) {
        music_player_.setMedia(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "music/menu_songs/" + content));
        music_player_.play();
    }
}

void Audio::PlaySound() {
    if (unmuted_) {
        sound_player_.setMedia(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "sound/life_lose.mp3"));
        sound_player_.play();
    }
}

void Audio::PlaySound(QString content) {
    if (unmuted_) {
        sound_player_.setMedia(
                   QUrl::fromLocalFile(kPathToAudio_ + "sound/" + content));
        sound_player_.play();
    }
}

void Audio::SetVolume(int volume) {
    music_player_.setVolume(volume);
    sound_player_.setVolume(volume);
}

void Audio::StopMusic() {
    music_player_.stop();
}

void Audio::StopSound() {
    sound_player_.stop();
}

void Audio::Mute(bool value) {
    unmuted_ = value;
}

void Audio::PauseMusic() {
    music_player_.pause();
}

void Audio::PauseSound() {
    sound_player_.pause();
}

void Audio::PreLoadMenuSongs() {
    QStringList content_names = QDir(
                kPathToAudio_ + "music/menu_songs/").entryList(QDir::Files);
    for (auto content_name : content_names) {
        menu_songs_.addMedia(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "music/menu_songs/" + content_name));
    }
    menu_songs_.setPlaybackMode(QMediaPlaylist::Loop);
}

void Audio::PreLoadGameSongs() {
    QStringList content_names = QDir(
                kPathToAudio_ + "music/game_songs/").entryList(QDir::Files);
    for (auto content_name : content_names) {
        game_songs_.addMedia(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "music/game_songs/" + content_name));
    }
    game_songs_.setPlaybackMode(QMediaPlaylist::Loop);
}
