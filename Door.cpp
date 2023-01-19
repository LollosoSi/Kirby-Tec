#include "Door.h"
#include "GameLoop.h"

#include "Sounds.h"
#include "Kirby.h"

using namespace KA;
void Door::launchAction(Kirby* instanceForConsistency) {


	if (!GameLoop::getInstance().loadGame(level, true, savecurrent)) {
		GameLoop::getInstance().loadGame(level, false, false);
	} 

	if (instanceForConsistency) {
		Kirby* k = ((Kirby*)GameLoop::getInstance().KirbyInstance);
		if(instanceForConsistency->status != KIRBY_FLY)
			k->setAbility(instanceForConsistency->status);
		else
			k->setAbility(HUD_POWER);
		k->setHealth(instanceForConsistency->getHealth());
	}
	


}