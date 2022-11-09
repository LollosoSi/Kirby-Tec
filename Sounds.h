#pragma once

#include <QSoundEffect>

namespace KA
{
	class Sounds;
}

class KA::Sounds
{
private:

	// sounds indexed by filename
	std::map< std::string, QSoundEffect*> _sounds;
	std::map< std::string, QSoundEffect*> _musics;

	Sounds();

public:

	// singleton
	static Sounds* instance();

	// controls
	void play(const std::string& id, bool music = false);
	void stopMusic(const std::string& id);
};