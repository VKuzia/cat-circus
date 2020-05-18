#include "audio.h"

QString Audio::kPathToAudio_ = QDir::currentPath() + "/data/audio/";
QMediaPlayer Audio::music_player_;
QMediaPlayer Audio::sound_player_;
bool Audio::unmuted_ = true;

QMediaPlaylist Audio::menu_songs_;
QMediaPlaylist Audio::game_songs_;
//QMap<QString, QMediaContent> Audio::sounds_;
//QMap<QString, QMediaContent> Audio::musics_;

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

//    PreLoadSounds();
//    PreLoadMusics();
}

void Audio::PlayMusic() {
//    music_player_.setPlaylist(sounds_);

//    music_player_.setMedia(QUrl::fromLocalFile(
//                                kPathToAudio + "music/menu_music.wav"));
//    QMediaContent content = QMediaContent(
//                QUrl::fromLocalFile(kPathToAudio_ + "music/menu_music.wav"));
//    music_player_.setMedia(content);
//    music_player_.play();
    music_player_.setPlaylist(&menu_songs_);
    music_player_.play();
}

void Audio::PlayMusic(QString content) {
//    music_player_.setMedia(musics_[content]);
    music_player_.setMedia(
                QUrl::fromLocalFile(kPathToAudio_ + "music/" + content));

//    music_player_.setPlaylist(&menu_songs_);
    music_player_.play();

}

void Audio::PlaySound() {
    sound_player_.setMedia(
                QUrl::fromLocalFile(kPathToAudio_ + "sound/life_lose.mp3"));
    sound_player_.play();
}

void Audio::PlaySound(QString content) {
//    sound_player_.setMedia(sounds_[content]);
    sound_player_.setMedia(
                QUrl::fromLocalFile(kPathToAudio_ + "sound/" + content));
    sound_player_.play();
}

void Audio::SwitchMusic() {

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
        menu_songs_.addMedia(QUrl::fromLocalFile(
                                  kPathToAudio_ + "music/menu_songs/" + content_name));
    }
    menu_songs_.setPlaybackMode(QMediaPlaylist::Loop);
}

void Audio::PreLoadGameSongs() {
    QStringList content_names = QDir(
                kPathToAudio_ + "music/game_songs/").entryList(QDir::Files);
    for (auto content_name : content_names) {
        game_songs_.addMedia(QUrl::fromLocalFile(
                                  kPathToAudio_ + "music/game_songs/" + content_name));
    }
    game_songs_.setCurrentIndex(0);
    game_songs_.setPlaybackMode(QMediaPlaylist::Loop);

}

//void Audio::PreLoadSounds() {
//    QStringList content_names = QDir(
//                kPathToAudio_ + "sound/").entryList(QDir::Files);
//    for (auto content_name : content_names) {
//        QMediaContent content = QMediaContent(
//                    QUrl::fromLocalFile(
//                        kPathToAudio_ + "sound/" + content_name));
//        sounds_.insert(content_name, content);
//    }
//}

//void Audio::PreLoadMusics() {
//    QStringList content_names = QDir(
//                kPathToAudio_ + "music/").entryList(QDir::Files);
//    for (auto content_name : content_names) {
//        QMediaContent content = QMediaContent(
//                    QUrl::fromLocalFile(
//                        kPathToAudio_ + "music/" + content_name));
//        sounds_.insert(content_name, content);
//    }
//}
