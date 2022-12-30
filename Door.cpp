#include "Door.h"
#include "GameLoop.h"

#include "Sounds.h"
#include "Kirby.h"

using namespace KA;
void Door::launchAction(Kirby* instanceForConsistency) {

	/*
	KA::Sounds::getInstance().stop("Vegetable Valley_Theme", 0);
	KA::Sounds::getInstance().stop("craft", 0);
	KA::Sounds::getInstance().stop("wii", 0);
	KA::Sounds::getInstance().stop("elevator", 0);
	KA::Sounds::getInstance().stop("Kirby_Adventure_theme", 0);
	KA::Sounds::getInstance().stop("pigstep", 0);

	KA::Sounds::getInstance().setVolume("Vegetable Valley_Theme", 0, volumecoefficient);
	KA::Sounds::getInstance().setVolume("craft", 0, volumecoefficient);
	KA::Sounds::getInstance().setVolume("wii", 0, volumecoefficient);
	KA::Sounds::getInstance().setVolume("elevator", 0, volumecoefficient);
	KA::Sounds::getInstance().setVolume("Kirby_Adventure_theme", 0, volumecoefficient);
	KA::Sounds::getInstance().setVolume("pigstep", 0, volumecoefficient); 

	if (level == std::string("levels/lobby")) {
		Sounds::instance()->playSound("wii.wav");
	}
	if (level == std::string("levels/level1")) {
		Sounds::instance()->playSound("craft.wav");
	}
	if (level == std::string("levels/level2")) {
		Sounds::instance()->playSound("pigstep.wav");
	}
	if (level == std::string("levels/elevator")) {
		Sounds::instance()->playSound("elevator.wav");
	}
*/

	if (!GameLoop::getInstance().loadGame(level, true, savecurrent)) {
		GameLoop::getInstance().loadGame(level, false, false);
	}

	if (instanceForConsistency) {
		Kirby* k = ((Kirby*)GameLoop::getInstance().KirbyInstance);
		k->setAbility(instanceForConsistency->status);
		k->setHealth(instanceForConsistency->getHealth());
	}
	


}