#include "GameLoop.h"

GameLoop::GameLoop()
{

}

GameLoop::~GameLoop()
{
		tickableObjects.clear();
		renderableObjects.clear();
}

// TODO: Implement loop
void GameLoop::loop() {

	while (running) {



	}

}

void GameLoop::start()
{
	running = true;

	std::thread loopthread(&GameLoop::loop, this);

}




void GameLoop::stop()
{
	running = false;
}
