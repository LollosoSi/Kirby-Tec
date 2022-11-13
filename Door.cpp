#include "Door.h"
#include "GameLoop.h"

void Door::launchAction() {
	
	if (!GameLoop::getInstance().loadGame(level, true, savecurrent)) {
		GameLoop::getInstance().loadGame(level, false, false);
	}
}