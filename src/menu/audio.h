#ifndef AUDIO_H
#define AUDIO_H

#include <QMediaPlayer>
#include <QDir>

class Audio {
 public:
  Audio();
  ~Audio() = default;

 signals:
  void AnimeReleased();

 public slots:
  void PlayMusic();
  void PlaySound();

  void SwitchMusic();
  void SwitchSound();
  void SetVolume();

  void Stop();
  void Finish();

 private:
  const QString kPathToAudio = QDir::currentPath() + "/data/audio/";

  QMediaPlayer* music_player_;
  QMediaPlayer* sound_player_;
};

#endif // AUDIO_H
