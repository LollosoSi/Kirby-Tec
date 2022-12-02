#include "Sounds.h"

#include <QDir>
#include <iostream>



using namespace KA;

Sounds::Sounds()
{
	QStringList sound_files = QDir("sounds/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : sound_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_sounds[name] = new QSoundEffect(this);
		_sounds[name]->setSource(QUrl::fromLocalFile(QString("sounds/") + f));
	}

	QStringList music_files = QDir("musics/").entryList(QStringList() << "*.mp3", QDir::Files);
	for (auto& f : music_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_musics[name] = new QSoundEffect(this);
		_musics[name]->setLoopCount(QSoundEffect::Infinite);
		_musics[name]->setSource(QUrl::fromLocalFile(QString("musics/") + f));
	}

	/*
	running = true;
	worker = std::thread([]() {

		

		std::vector<std::pair<std::string, bool>> cp;
		while (Sounds::getInstance().running)

			cp = Sounds::getInstance().execlist;
			Sounds::getInstance().execlist.clear();
			for (auto& item : cp) {
				
				if (!item.second && Sounds::getInstance()._sounds.find(item.first) != Sounds::getInstance()._sounds.end()) {
					Sounds::getInstance()._sounds[item.first]->stop();
					Sounds::getInstance()._sounds[item.first]->play();
				}
				else if (item.second && Sounds::getInstance()._musics.find(item.first) != Sounds::getInstance()._musics.end()) {
					Sounds::getInstance()._musics[item.first]->play();
				}
			
			}

			std::this_thread::sleep_for(std::chrono::nanoseconds(200));

		});
*/		
}

void Sounds::playfile(const std::string& id, bool music) {

		if (!music && _sounds.find(id) != _sounds.end()) {
			//_sounds[id]->stop();
			//_sounds[id]->moveToThread(new QThread());
			//_sounds[id]->play();

			QSoundEffect* qs = new QSoundEffect();
			qs->setSource(_sounds[id]->source().toString());
			//qs->startTimer(6000);
			qs->play();
			qs->deleteLater();
			playingsounds.insert(std::pair<std::string, QSoundEffect*>(id, qs));
			
			
		}
		else if (music && _musics.find(id) != _musics.end()) {
			_musics[id]->play();
		}
		else {
			std::cout << "Cannot play\n";
		}

		//std::cout << "Playing " << id << "\n";
	
}

void Sounds::stop(const std::string& id, bool music) {

	stoplist.push_back(std::pair<std::string, bool>(id, music));

}

void Sounds::stopfile(const std::string& id, bool music) {

	if (!music && playingsounds.find(id) != playingsounds.end()) {
		playingsounds[id]->stop();
		playingsounds[id]->deleteLater();
		playingsounds.erase(playingsounds.find(id));
	}
	else if (music && _musics.find(id) != _musics.end()) {
		_musics[id]->stop();
	}
	else {
		std::cout << "Cannot play\n";
	}

}


void Sounds::play(const std::string id, bool music)
{
	//playfile(id,music);
	execlist.push_back(std::pair<std::string, bool>(id, music));

	
}

void Sounds::setVolume(const std::string& id, bool music, double volume)

{
	if (!music && _sounds.find(id) != _sounds.end()) {
		_sounds[id]->setVolume(volume);
	}
	else if (music && _musics.find(id) != _musics.end()) {
		_musics[id]->setVolume(volume);
	}

}

void Sounds::stopMusic(const std::string& id)
{
	if (_musics.find(id) != _musics.end())
		_musics[id]->stop();
}

void Sounds::run() {
	running = 1;
	std::vector<std::pair<std::string, bool>> cp;
	
	while (running) {

		cp = Sounds::getInstance().execlist;
		Sounds::getInstance().execlist.clear();
		for (auto& item : cp) {

			playfile(item.first, item.second);

		}


		cp = Sounds::getInstance().stoplist;
		Sounds::getInstance().stoplist.clear();
		for (auto& item : cp) {
			stopfile(item.first, item.second);

		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(200));
	}


}