#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

// Khai b�o h�m �m thanh
bool loadAudio();
void playJumpSound();
void playLevelUpSound();
void playGameOverSound();
void playBackgroundMusic();
void stopBackgroundMusic();
void cleanupAudio();

#endif

