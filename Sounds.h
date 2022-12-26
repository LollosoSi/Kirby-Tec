
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
	void playSound(const std::string& id);
	void playLoopedSound(const std::string& id, bool loop = true);
	void stopSound(const std::string& id);
};