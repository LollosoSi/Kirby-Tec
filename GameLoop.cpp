#include "GameLoop.h"
#include "Vec2D.h"
#include "Camera.h"
#include "CollisionDetection.h"


GameLoop::GameLoop() {}

GameLoop::~GameLoop() {
	tickableObjectsQueue.clear();
	renderableObjectsQueue.clear();
	serializableObjects.clear();
	collidableObjects.clear();
}

void GameLoop::recalculateTicks(int target_ticks) {
	(*this).target_ticks = target_ticks;
	min_delta_millis_tick = target_ticks != 0 ? 1000 / target_ticks : 0;
}

void GameLoop::recalculateFps(int target_fps) {
	(*this).target_fps = target_fps;
	min_delta_millis_fps = target_fps != 0 ? 1000 / target_fps : 0;
}

// TODO: Implement loop
void GameLoop::loop() {

	//recalculateTicks(20);
	//recalculateFps(75);

	QTime current = QTime::currentTime();

	int fps = 0, ticks = 0;
	last_millis_render = current, last_millis_tick = current, last_log = current;

	long deltasum = 0;
	long deltas = 0;

	int delta_tick, delta_fps, delta_log = 0;
	while (running) {
		current = QTime::currentTime();

		if ((delta_tick = last_millis_tick.msecsTo(current)) >= min_delta_millis_tick)
		{
			deltas++;
			deltasum += delta_tick;

			last_millis_tick = current;
			ticks++;

			tick(delta_tick / 1000.0);
		}
		if (!waitingForRender)
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
			std::cout << "DeltaAvg: " << (deltasum / deltas) << "\t";
			std::cout << "Ticks: " << ticks << "\t";
			std::cout << "Frames: " << fps << std::endl;
			ticks = 0;
			fps = 0;
		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(2));

	}

}

void GameLoop::saveGame(std::ostream &out) {
	char separator = '#';
	for (auto* item : this->serializableObjects) 
		out << item->serialize(obj_separator) << separator;

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

	for (auto* item : this->serializableObjectsQueue)
		this->serializableObjects.push_back(item);
	serializableObjectsQueue.clear();

	for (auto* item : this->collidableObjectsQueue)
		this->collidableObjects.push_back(item);
	collidableObjectsQueue.clear();
}

void GameLoop::render() {
	waitingForRender = true;
	emit(pleaseRender(&renderableObjects));
}

void GameLoop::tick(double deltatime) {

	Camera::getInstance().tick(deltatime);
	for (auto* item : this->tickableObjects) 
		item->tick(deltatime);
	
	for (auto* item : this->particleObjects)
		if (item->shouldDelete()) {
			renderableObjects.erase(std::find(renderableObjects.begin(), renderableObjects.end(), item));
			tickableObjects.erase(std::find(tickableObjects.begin(), tickableObjects.end(), item));
			particleObjects.erase( std::find(particleObjects.begin(), particleObjects.end(), item) );
		}

}

void GameLoop::start() {
	running = true;

	loopthread = std::thread(&GameLoop::loop, this);

}

void GameLoop::stop() {
	running = false;
	loopthread.join();
}

void GameLoop::addKirby(Kirby& kb) {

	KirbyInstance = &kb;
	addToTickable(&kb);
	addToRenderable(&kb);
	addToCollidable(&kb);
	addToSerializable(&kb);

}

void GameLoop::addTerrain(Terrain& t) {
	addToRenderable(&t);
	addToCollidable(&t);
	addToSerializable(&t);
}


void GameLoop::addToTickable(TickableObject* tco) {
	this->tickableObjectsQueue.push_back(tco);
}

void GameLoop::addToRenderable(RenderableObject* rdo) {
	this->renderableObjectsQueue.push_back(rdo);
}

void GameLoop::addToSerializable(Serializable* s) {
	this->serializableObjectsQueue.push_back(s);
}

void GameLoop::addToCollidable(RigidBody* s) {
	this->collidableObjectsQueue.push_back(s);
}

void GameLoop::addParticle(Particle* p) {

	addToRenderable(p);
	addToTickable(p);
	
	particleObjects.push_back(p);
}


void GameLoop::keyPressEvent(QKeyEvent* e, bool isPressed) {
	

	// game controls
	if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
		KirbyInstance->buttons[Kirby::DOWN] = isPressed;
	if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
		KirbyInstance->buttons[Kirby::RIGHT] = isPressed;
	if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
		KirbyInstance->buttons[Kirby::LEFT] = isPressed;
	if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
		KirbyInstance->buttons[Kirby::UP] = isPressed;

	if (e->key() == Qt::Key_R)
	{
		KirbyInstance->setX(0); KirbyInstance->setY(-500);
	}

	if (e->isAutoRepeat())
		return;

	if (e->key() == Qt::Key_Space)
		KirbyInstance->buttons[Kirby::SPACE] = isPressed;

	std::cout << (isPressed ? "Pressed: " : "Released: ") << e->key() << "\n";
}

std::vector<std::pair<RigidBody*, double>> GameLoop::findCollisions(RigidBody* rb) {

	PB::Vec2Df cp, cn;
	double ct = 0, min_t = INFINITY;
	std::vector<std::pair<RigidBody*, double>> sortedByContactTime;
	for (RigidBody* obj : collidableObjects)
		if(obj != rb)
		if (DynamicRectVsRect(rb->getColliderRectF(), rb->getVelocity(), obj->getColliderRectF(), cp, cn, ct))
			sortedByContactTime.push_back({ obj, ct });
	std::sort(sortedByContactTime.begin(), sortedByContactTime.end(),
		[this](const std::pair<RigidBody*, double>& a, const std::pair<RigidBody*, double>& b)
		{
			// if contact time is the same, give priority to nearest object
			return a.second != b.second ? a.second < b.second : 0;
		});

	return sortedByContactTime;
}
