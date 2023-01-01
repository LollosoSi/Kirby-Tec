
#include <QDir>
#include "Sounds.h"

#include <thread>

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
		_sounds[QFileInfo(f).baseName().toStdString()] = new QSoundEffect();
	

	std::thread t = std::thread([](Sounds* instance, QStringList sound_files) {

	for (auto& f : sound_files) {
		std::string name = QFileInfo(f).baseName().toStdString();
		instance->_sounds[name]->setSource(QUrl::fromLocalFile(QString("sounds/") + f));
	}

		}, this, sound_files);
	t.detach();

	
}

void Sounds::playSound(const std::string& id)
{
	if (_sounds.find(id) != _sounds.end())
		_sounds[id]->play();
}

void Sounds::playLoopedSound(const std::string& id, bool loop)
{
	if (_sounds.find(id) != _sounds.end())
	{
		if (loop)
			_sounds[id]->setLoopCount(QSoundEffect::Infinite);
		_sounds[id]->play();
	}
}

void Sounds::stopSound(const std::string& id)
{
	if (_sounds.find(id) != _sounds.end()) {
		do {
			
			_sounds[id]->stop();
		} while (_sounds[id]->isPlaying());
	}
}