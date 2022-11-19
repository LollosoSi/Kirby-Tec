#include "Door.h"
#include "GameLoop.h"

#include "Sounds.h"

void Door::launchAction() {

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
		KA::Sounds::getInstance().play("wii", 0);
	}
	if (level == std::string("levels/level1")) {
		KA::Sounds::getInstance().play("craft", 0);
	}
	if (level == std::string("levels/level2")) {
		KA::Sounds::getInstance().play("pigstep", 0);
	}
	if (level == std::string("levels/elevator")) {
		KA::Sounds::getInstance().play("elevator", 0);
	}



	if (!GameLoop::getInstance().loadGame(level, true, savecurrent)) {
		GameLoop::getInstance().loadGame(level, false, false);
	}
}