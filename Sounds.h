#pragma once

#include <QSoundEffect>

namespace KA
{
	class Sounds;
}

class KA::Sounds
{
private:
	// Relativi al singleton
	Sounds();
	Sounds(Sounds const&) = delete;
	void operator=(Sounds const&) = delete;
	//

	// sounds indexed by filename
	std::map< std::string, QSoundEffect*> _sounds;
	std::map< std::string, QSoundEffect*> _musics;


public:
	// Relativi al singleton
	static Sounds& getInstance() { static Sounds instance; return instance; }
	~Sounds() {}

	

	// controls
	void play(const std::string& id, bool music = false);
	void stopMusic(const std::string& id);
};