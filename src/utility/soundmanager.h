#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundManager {
 public:
  SoundManager();
  enum sounds { kButtonClick };
  void PlaySound(int sound);  // plays given sound
};

#endif  // SOUNDMANAGER_H
