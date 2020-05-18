#include "audio.h"

QString Audio::kPathToAudio_ = QDir::currentPath() + "/data/audio/";
QMediaPlayer Audio::music_player_;
QMediaPlayer Audio::sound_player_;
QMap<QString, QMediaContent> Audio::sounds_;
QMap<QString, QMediaContent> Audio::musics_;

Audio::Audio() {
//    sounds_.addMedia(QUrl::fromLocalFile(
//                          kPathToAudio + "sound/button_click.ogg"));
//    sounds_.addMedia(QUrl::fromLocalFile(
//                          kPathToAudio + "sound/game_over.flac"));
//    sounds_.addMedia(QUrl::fromLocalFile(
//                          kPathToAudio + "sound/life_lose.mp3"));
//    sounds_.setCurrentIndex(1);
//    sounds_.setPlaybackMode(QMediaPlaylist::Loop);
//    sound_player_.setPlaylist(sounds_);
//    music_player_.setPlaylist(sounds_);

    PreLoadSounds();
    PreLoadMusics();
//    connect(music_player_, Audio::MenuSongFinished(), this, Audio::PlayMusic());
}

void Audio::PlayMusic() {
//    music_player_.setPlaylist(sounds_);

//    music_player_.setMedia(QUrl::fromLocalFile(
//                                kPathToAudio + "music/menu_music.wav"));
    QMediaContent content = QMediaContent(
                QUrl::fromLocalFile(kPathToAudio_ + "music/menu_music.wav"));
    music_player_.setMedia(content);
    music_player_.play();

}

void Audio::PlaySound() {
    sound_player_.setMedia(
                QUrl::fromLocalFile(kPathToAudio_ + "sound/life_lose.mp3"));
    sound_player_.play();
}

void Audio::PlaySound(QString content) {
    sound_player_.setMedia(sounds_[content]);
    sound_player_.play();
}

void Audio::SwitchMusic() {

}

void Audio::SetVolume(int volume) {
    music_player_.setVolume(volume);
    sound_player_.setVolume(volume);
}

void Audio::Stop() {
    music_player_.stop();
    sound_player_.stop();
}

void Audio::PreLoadSounds() {
    QStringList content_names = QDir(
                kPathToAudio_ + "sound/").entryList(QDir::Files);
    for (auto content_name : content_names) {
        QMediaContent content = QMediaContent(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "sound/" + content_name));
        sounds_.insert(content_name, content);
    }
}

void Audio::PreLoadMusics() {
    QStringList content_names = QDir(
                kPathToAudio_ + "music/").entryList(QDir::Files);
    for (auto content_name : content_names) {
        QMediaContent content = QMediaContent(
                    QUrl::fromLocalFile(
                        kPathToAudio_ + "music/" + content_name));
        sounds_.insert(content_name, content);
    }
}
