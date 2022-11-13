#include "GameLoop.h"
#include "Vec2D.h"
#include "Camera.h"
#include "CollisionDetection.h"
#include "Sounds.h"
#include "Sprites.h"
#include "LevelBuilder.h"


GameLoop::GameLoop() {

}

GameLoop::~GameLoop() {
	clear();
	stop();
	if (loopthread.joinable())
		loopthread.join();
}

void GameLoop::recalculateTicks(int target_ticks) {
	(*this).target_ticks = target_ticks;
	min_delta_millis_tick = target_ticks != 0 ? 1000 / target_ticks : 0;
}

void GameLoop::recalculateFps(int target_fps) {
	(*this).target_fps = target_fps;
	min_delta_millis_fps = target_fps != 0 ? 1000 / target_fps : 0;
}

void GameLoop::loop() {
	//std::cout << "Loop started\n";

	thread_working = true;

	QTime current = QTime::currentTime();

	int fps = 0, ticks = 0;
	last_millis_render = current, last_millis_tick = current, last_log = current;

	long deltasum = 0;
	long deltas = 0;

	int delta_tick, delta_fps, delta_log = 0;
	while (running) {
		
			current = QTime::currentTime();
			if (!waitingForRender) {
				if (!paused) {
					if ((delta_tick = last_millis_tick.msecsTo(current)) >= min_delta_millis_tick) {
						deltas++;
						deltasum += delta_tick;

						last_millis_tick = current;
						ticks++;

						tick(delta_tick / 1000.0);

						if (!this->tickableObjectsQueue.empty() || !this->renderableObjectsQueue.empty())
							mergeQueues();

					}
				}
				else
					last_millis_tick = current;


				if ((delta_fps = last_millis_render.msecsTo(current)) >= min_delta_millis_fps)
				{
					last_millis_render = current;
					fps++;

					render();
				}
			}

		if (deltas > 0 && (delta_log = last_log.msecsTo(current)) >= 1000) {
			last_log = current;
			std::cout << "DeltaAvg: " << (deltasum / deltas) << "\t";
			std::cout << "Ticks: " << ticks << "\t";
			std::cout << "Frames: " << fps << std::endl;
			ticks = 0;
			fps = 0;
		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(2));

	}
	thread_working = false;
	//std::cout << "Loop done\n";

}

void GameLoop::saveGame(std::string fileName) {
	Serializer::serializeToFile(serializableObjects, fileName);
}

bool GameLoop::loadGame(std::string fileName) {
	clear();

	std::vector<Serializable*> tempserializableObjects = Serializer::deserializeFromFile(fileName);

	for (Serializable* item : tempserializableObjects) {
		GameObject* obj = dynamic_cast<GameObject*>(item);
		switch (obj->getObjectId()) {
		case objects::GAMEOBJECT:
			break;
		
		case objects::KIRBY:
			addKirby(obj);
			break;

		case objects::BACKGROUND:
			addTerrain(obj);
			tickableObjects.push_back(dynamic_cast<TickableObject*>(obj));
			break;

		case objects::TERRAIN:
			addTerrain(obj);
			break;

		case objects::DOOR:
			GameLoop::getInstance().addToSerializable(dynamic_cast<GameObject*>(obj));
			GameLoop::getInstance().addToCollidable(dynamic_cast<RigidBody*>(obj));
			GameLoop::getInstance().addToRenderable(dynamic_cast<RenderableObject*>(obj));
			break;

		case objects::STEPUP:
			addTerrain(obj);
			break;

		case objects::SLOPED_TERRAIN_25:
			addTerrain(obj);
			break;
		case objects::SLOPED_TERRAIN_45:
			addTerrain(obj);
			break;
		case objects::SLOPED_TERRAIN_205:
			addTerrain(obj);
			break;
		case objects::SLOPED_TERRAIN_225:
			addTerrain(obj);
			break;
		}
	
	}	

	return tempserializableObjects.size() != 0;

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

void GameLoop::render(bool clear) {
	waitingForRender = true;
	emit(pleaseRender(clear));
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
			delete item;
		}

}

void GameLoop::start() {
	running = true;
	paused = false;
	// KA::Sounds::instance()->play("Kirby_Adventure_theme");
	
	
	if(!loopthread.joinable())
		loopthread = std::thread(&GameLoop::loop, this);

	
}


void GameLoop::pause(bool pause) {
	paused = pause;
	
}

void GameLoop::stop() {
	running = false;
	paused = false;

	//GameLoop::getInstance().saveGame("testout");
	
}

void GameLoop::addKirby(GameObject* kb) {

	KirbyInstance = kb;
	addToTickable(dynamic_cast<TickableObject*>(kb));
	addToRenderable(dynamic_cast<RenderableObject*>(kb));
	addToCollidable(dynamic_cast<RigidBody*>(kb));
	addToSerializable(dynamic_cast<Serializable*>(kb));

}

void GameLoop::addTerrain(GameObject* t) {
	addToRenderable(dynamic_cast<RenderableObject*>(t));
	addToCollidable(dynamic_cast<RigidBody*>(t));
	addToSerializable(dynamic_cast<Serializable*>(t));
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
	
	// Pause
	if (e->key() == Qt::Key_P && isPressed) {
		
		if (paused) {
			start();
		} else { 
			pause(); 
		}
	}
	// Save
	if (e->key() == Qt::Key_K)
		GameLoop::getInstance().saveGame("level2");


	if (e->key() == Qt::Key_R)
	{
		KirbyInstance->setX(4); KirbyInstance->setY(-4);
	}

	if (e->isAutoRepeat())
		return;


	if (e->key() == Qt::Key_1 && !isPressed) {
		GameLoop::getInstance().loadGame("levels/level1");
		KA::Sounds::getInstance().play("Vegetable Valley_Theme");
	}

	if (e->key() == Qt::Key_2 && !isPressed) {

		//Camera::getInstance().setX(0);
		//Camera::getInstance().setY(-8);

		
		if (!GameLoop::getInstance().loadGame("levels/level2")) {

			Background* bkgrnd = new Background(QPointF(0, -8), QPointF(0, 0), 400, 500, objects::BACKGROUND, TexID::BACKGROUND1);
			GameLoop::getInstance().addToRenderable(dynamic_cast<RenderableObject*>(bkgrnd));
			GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(bkgrnd));
			GameLoop::getInstance().addToSerializable(dynamic_cast<Serializable*>(bkgrnd));

			Kirby* k = new Kirby(QPointF(0.0, -5.0));
			GameLoop::getInstance().addKirby(dynamic_cast<GameObject*>(k));			

		}

		//KA::Sounds::getInstance().play("Vegetable Valley_Theme");

		
	}

	if (e->key() == Qt::Key_3 && !isPressed) {

		//Camera::getInstance().setX(0);
		//Camera::getInstance().setY(-8);


		if (!GameLoop::getInstance().loadGame("levels/lobby")) {

			Background* bkgrnd = new Background(QPointF(0, -8), QPointF(0, 0), 400, 500, objects::BACKGROUND, TexID::LOBBY);
			GameLoop::getInstance().addToRenderable(dynamic_cast<RenderableObject*>(bkgrnd));
			GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(bkgrnd));
			GameLoop::getInstance().addToSerializable(dynamic_cast<Serializable*>(bkgrnd));

			Kirby* k = new Kirby(QPointF(0.0, -5.0));
			GameLoop::getInstance().addKirby(dynamic_cast<GameObject*>(k));

		}

		//KA::Sounds::getInstance().play("Vegetable Valley_Theme");


	}

	
	if(KirbyInstance)
		KirbyInstance->keyPressEvent(e,isPressed);
	else {
		// Controls
		if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
			Camera::getInstance().setY(Camera::getInstance().getY()+10);
		if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() + 10);
		if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() - 10);
		if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
			Camera::getInstance().setY(Camera::getInstance().getY() - 10);


	}

	std::cout << (isPressed ? "Pressed: " : "Released: ") << e->key() << "\n";
}

std::vector<std::pair<RigidBody*, double>> GameLoop::findCollisions(RigidBody* rb) {

	KA::Vec2Df cp, cn;
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
			return a.second != b.second ? a.second < b.second : pitagoricDistance(a.first->getCollider().center(), b.first->getCollider().center()) < 0;
		});

	return sortedByContactTime;
}
void GameLoop::clear() {
	
	//stop();

	
	
	std::thread t([]() {
		
		GameLoop::getInstance().stop();
		GameLoop::getInstance().loopthread.join();
		
		GameLoop::getInstance().render(true);
	

		});
	
	if(t.joinable())
		t.join();

	std::vector<GameObject*> obj;

	// Avoid memory leaks
	for (auto* item : this->renderableObjects)
	{
		std::vector<GameObject*>::iterator it = std::find(obj.begin(), obj.end(), dynamic_cast<GameObject*>(item));
		if (it != obj.end())
			obj.push_back(dynamic_cast<GameObject*>(item));
	}
	for (auto* item : this->tickableObjects)
	{
		std::vector<GameObject*>::iterator it = std::find(obj.begin(), obj.end(), dynamic_cast<GameObject*>(item));
		if (it != obj.end())
			obj.push_back(dynamic_cast<GameObject*>(item));
	}
	for (auto* item : this->particleObjects)
	{
		std::vector<GameObject*>::iterator it = std::find(obj.begin(), obj.end(), dynamic_cast<GameObject*>(item));
		if (it != obj.end())
			obj.push_back(dynamic_cast<GameObject*>(item));
	}
	for (auto* item : this->serializableObjects)
	{
		std::vector<GameObject*>::iterator it = std::find(obj.begin(), obj.end(), dynamic_cast<GameObject*>(item));
		if (it != obj.end())
			obj.push_back(dynamic_cast<GameObject*>(item));
	}
	for (auto* item : this->collidableObjects)
	{
		std::vector<GameObject*>::iterator it = std::find(obj.begin(), obj.end(), dynamic_cast<GameObject*>(item));
		if (it != obj.end())
			obj.push_back(dynamic_cast<GameObject*>(item));
	}

	for (auto* item : obj)
	{
		delete item;
	}

	tickableObjects.clear();
	renderableObjects.clear();
	serializableObjects.clear();
	collidableObjects.clear();
	particleObjects.clear();

	GameLoop::getInstance().start();

}
