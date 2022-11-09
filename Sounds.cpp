#include <QDir>
#include "Sounds.h"

using namespace KA;

Sounds* Sounds::instance()
{
	static Sounds uniqueInstance;
	return &uniqueInstance;
}

Sounds::Sounds()
{
	QStringList sound_files = QDir("sounds/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : sound_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_sounds[name] = new QSoundEffect();
		_sounds[name]->setSource(QUrl::fromLocalFile(QString("sounds/") + f));
	}

	QStringList music_files = QDir("musics/").entryList(QStringList() << "*.mp3", QDir::Files);
	for (auto& f : music_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_musics[name] = new QSoundEffect();
		_musics[name]->setLoopCount(QSoundEffect::Infinite);
		_musics[name]->setSource(QUrl::fromLocalFile(QString("musics/") + f));
	}
}

void Sounds::play(const std::string& id, bool music)
{
	if (!music && _sounds.find(id) != _sounds.end())
		_sounds[id]->play();
	else if (music && _musics.find(id) != _musics.end())
		_musics[id]->play();
}

void Sounds::stopMusic(const std::string& id)
{
	if (_musics.find(id) != _musics.end())
		_musics[id]->stop();
}
