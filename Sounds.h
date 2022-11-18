#pragma once

#include <QSoundEffect>
#include <QtMultimedia/QMediaPlayer>
#include "TickableObject.h"
#include <thread>

namespace KA
{
	class Sounds;
}

class KA::Sounds : public QObject, public TickableObject
{
	Q_OBJECT

private:
	void playfile(const std::string& id, bool music = false);

	// Relativi al singleton
	Sounds();
	Sounds(Sounds const&) = delete;
	void operator=(Sounds const&) = delete;
	//

	// sounds indexed by filename
	std::map< std::string, QSoundEffect*> _sounds;
	std::map< std::string, QSoundEffect*> _musics;


	std::thread worker;
	bool running = false;

public:
	// Relativi al singleton
	static Sounds& getInstance() { static Sounds instance; return instance; }
	~Sounds() {
		running = false;
		if(worker.joinable())
			worker.join();
	}

	std::vector <std::pair<std::string, bool>> execlist;

	void tick(double delta) {
	
		for (auto item : execlist)
			playfile(item.first, item.second);
		execlist.clear();
	
	}

	

	// controls
	void play(const std::string& id, bool music = false);
	void stopMusic(const std::string& id);
	void stop(const std::string& id, bool music = false);
};