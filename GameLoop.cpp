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

void GameLoop::recalculateTicks(int target_ticks) {
	(*this).target_ticks = target_ticks;
	min_delta_millis_tick = target_ticks != 0 ? 1000/target_ticks : 0;
}

void GameLoop::recalculateFps(int target_fps) {
	(*this).target_fps = target_fps;
	min_delta_millis_fps = target_fps != 0 ? 1000 / target_fps : 0;
}

// TODO: Implement loop
void GameLoop::loop() {

	recalculateTicks(100);
	recalculateFps(75);

	QTime current = QTime::currentTime();

	int fps = 0, ticks = 0;
	last_millis_render = current, last_millis_tick = current, last_log = current;
	
	long deltasum = 0;
	long deltas = 0;

	int delta_tick, delta_fps, delta_log = 0;
	while (running) {
		current = QTime::currentTime();

		if ((delta_tick=last_millis_tick.msecsTo(current)) >= min_delta_millis_tick)
		{
			deltas++;
			deltasum += delta_tick;
			
			last_millis_tick = current;
			ticks++;

			tick(delta_tick/1000.0);
		}
		if(!waitingForRender)
		if ((delta_fps = last_millis_render.msecsTo(current)) >= min_delta_millis_fps)
		{
			last_millis_render = current;
			fps++;

			render();
		}

		if (!this->tickableObjectsQueue.empty() || !this->renderableObjectsQueue.empty())
			mergeQueues();
		
		if ((delta_log = last_log.msecsTo(current)) >= 1000) {
			last_log = current;
			std::cout << "DeltaAvg: " << (deltasum/deltas) << "\t";
			std::cout << "Ticks: " << ticks << "\t";
			std::cout << "Frames: " << fps << std::endl;
			ticks = 0;
			fps = 0;
		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(10));

	}

}

void GameLoop::renderingCompleted() {
	this->last_millis_render = QTime::currentTime();
	this->waitingForRender = false;
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
	waitingForRender = true;
	emit(pleaseRender(&renderableObjects));
}

void GameLoop::tick(double deltatime) {

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
