#include "Door.h"
#include "GameLoop.h"

void Door::launchAction() {

	if (!GameLoop::getInstance().loadGame(level + std::string(".save"))) {
		GameLoop::getInstance().loadGame(level);
	}
}