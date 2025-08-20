#pragma once
#include <fmod.hpp>
#include <iostream>
#include "Dictionary.h"

static class AudioManager
{
private:
	static FMOD::System* _audioSystem;
	static Dictionary<std::string, FMOD::Sound*> _soundEffects;
	static Dictionary<std::string, FMOD::Sound*> _music;
	static FMOD::Channel* _musicChannel;
public:
	static void init();
	static void addSound(std::string sfxName, std::string sfxDirectory);
	static void playSound(std::string sfxName);
	static void playSound(std::string sfxName, float pitch);
	static void addSong(std::string songName, std::string songDirectory);
	static void playSong(std::string songName);
	static void stopMusic();
private:
	static void debugResult(FMOD_RESULT result);
};