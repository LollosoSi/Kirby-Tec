#include "GameLoop.h"



GameLoop::GameLoop(){
	//pippo* pippi = 
	//addToRenderable(pippi);
	
	

}

GameLoop::~GameLoop()
{
		tickableObjectsQueue.clear();
		renderableObjectsQueue.clear();
}

// TODO: Implement loop
void GameLoop::loop() {

	QTime current = QTime::currentTime();

	int fps = 0, ticks = 0;
	int target_ticks = 20, target_fps = 60;
	int min_delta_millis_fps = 1000 / target_fps, min_delta_millis_tick = 1000/target_ticks;
	QTime last_millis_render = current, last_millis_tick = current;
	
	int delta_tick, delta_fps;
	while (running) {
		current = QTime::currentTime();

		if ((delta_tick=last_millis_tick.msecsTo(current)) > min_delta_millis_tick)
		{
			last_millis_tick = current;
			ticks++;

			tick(delta_tick);
		}

		if ((delta_fps = last_millis_render.msecsTo(current)) > min_delta_millis_fps)
		{
			last_millis_render = current;
			fps++;

			render();
		}

		if (!this->tickableObjectsQueue.empty() || !this->renderableObjectsQueue.empty())
			mergeQueues();
		

		std::this_thread::sleep_for(std::chrono::milliseconds(2));

	}

}

void GameLoop::mergeQueues() {

	for (auto* item : this->tickableObjectsQueue)
		this->tickableObjects.push_back(item);
	tickableObjectsQueue.clear();

	for (auto* item : this->renderableObjectsQueue)
		this->renderableObjects.push_back(item);
	renderableObjectsQueue.clear();
}

void GameLoop::render() {
	emit(pleaseRender(&renderableObjects));
}

void GameLoop::tick(int deltatime) {

	for (auto* item : this->tickableObjects) {
		item->tick(deltatime);
	}

}

void GameLoop::start()
{
	running = true;

	loopthread = std::thread(&GameLoop::loop, this);
	
}

void GameLoop::stop()
{
	running = false;
	loopthread.join();
}

void GameLoop::addToTickable(TickableObject* tco)
{
	this->tickableObjectsQueue.push_back(tco);
}

void GameLoop::addToRenderable(RenderableObject* rdo)
{
	this->renderableObjectsQueue.push_back(rdo);
}
