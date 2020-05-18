#ifndef AUDIO_H
#define AUDIO_H

#include <QMediaPlayer>
#include <QDir>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QMap>

class Audio {
 public:
  Audio();
  ~Audio() = default;

  static void Mute(bool value);

  static void PreLoadMenuSongs();
  static void PreLoadGameSongs();

 public slots:
  static void PlayMenuMusic();
  static void PlayGameMusic();
  static void PlayMusic(QString content);
  static void PlaySound();
  static void PlaySound(QString content);

  static void SetVolume(int volume);

  static void StopMusic();
  static void StopSound();

  static void PauseMusic();
  static void PauseSound();

 private:
  static QString kPathToAudio_;
  static QMediaPlayer music_player_;
  static QMediaPlayer sound_player_;
  static bool unmuted_;
  static QMediaPlaylist menu_songs_;
  static QMediaPlaylist game_songs_;
};

#endif  // AUDIO_H
