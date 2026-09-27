#ifndef SONG_H
#define SONG_H

#include <Arduino.h>
#include "LightStyle.h" 

class Song {
  private:
    int _trackId;
    LightStyle* _style;       // 🔴 MUST HAVE THE STAR HERE
    bool _isPlaying;         

  public:
    Song(int trackId, LightStyle* style); // 🔴 MUST HAVE THE STAR HERE

    void play();
    void update();
    void stop();
};

#endif
