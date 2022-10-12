#include "GameLoop.h"

GameLoop::GameLoop(){}

GameLoop::~GameLoop()
{
		tickableObjects.clear();
		renderableObjects.clear();
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
		

		std::this_thread::sleep_for(std::chrono::milliseconds(2));

	}

}

void GameLoop::render() {
	scene->clear();

	for (auto& item : this->renderableObjects) {
		item.render(*scene);
	}


}

void GameLoop::tick(int deltatime) {

	for (auto& item : this->tickableObjects) {
		item.tick(deltatime);
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
