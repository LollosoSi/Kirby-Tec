#include "GameLoop.h"
#include "Vec2D.h"
#include "Camera.h"
#include "CollisionDetection.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Definitions.h"

GameLoop::GameLoop() {
	pauseGUI = new BaseGUI(QPointF(0, 0), TexManager::HUD_PAUSE_SCREEN, 3);
	pauseSuggestion = new BaseGUI(QPointF(0.0968543, 0.0368969), TexManager::HUD_PAUSE_BACKDROP, 4);
}

GameLoop::~GameLoop() {
	clear();
	stop();
	if (loopthread.joinable())
		loopthread.join();
	
	delete pauseGUI;
}

void GameLoop::recalculateTicks(int target_ticks) {
	(*this).target_ticks = target_ticks;
	min_delta_millis_tick = target_ticks != 0 ? 1000 / target_ticks : 0;
}

void GameLoop::recalculateFps(int target_fps) {
	(*this).target_fps = target_fps;
	min_delta_millis_fps = target_fps != 0 ? 1000 / target_fps : 0;
}

std::vector<RigidBody*> GameLoop::getInside(RigidBody* rb, QRectF area) {
	bool usearea = area.width() != 0;
	std::vector<RigidBody*> objs;
	for (RigidBody* obj : collidableObjects)
		if (obj != rb && obj->getObjectId() != objects::BACKGROUND)
			if ((usearea ? area : rb->getCollider()).intersects(obj->getCollider()))
				objs.push_back(obj);
	return objs;
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

void GameLoop::reload() {
	loadGame(currentlevel, false, false);
}

void GameLoop::addElement(GameObject* obj) {

	bool* chars = obj->getObjectCharacteristics();
	if (chars[0])
		addToTickable(dynamic_cast<TickableObject*>(obj));
	if (chars[1])
		addToRenderable(dynamic_cast<RenderableObject*>(obj));
	if (chars[2])
		addToCollidable(dynamic_cast<RigidBody*>(obj));
	if (chars[3])
		addToSerializable(dynamic_cast<Serializable*>(obj));
	if (chars[4])
		KirbyInstance = obj;

	delete[] chars;
}

void GameLoop::removeElement(GameObject* obj) {
	bool* chars = obj->getObjectCharacteristics();
	if (chars[0]) {
		std::vector<TickableObject*>::iterator it = std::find(tickableObjects.begin(), tickableObjects.end(), dynamic_cast<TickableObject*>(obj));
		if (it != tickableObjects.end())
			tickableObjects.erase(it);
	}
	if (chars[1]) {
		std::vector<RenderableObject*>::iterator it = std::find(renderableObjects.begin(), renderableObjects.end(), dynamic_cast<RenderableObject*>(obj));
		if (it != renderableObjects.end()) {
			renderableObjectsToBeDeleted.push_back(*it);
			renderableObjects.erase(it);
		}
	}
	if (chars[2]) {
		std::vector<RigidBody*>::iterator it = std::find(collidableObjects.begin(), collidableObjects.end(), dynamic_cast<RigidBody*>(obj));
		if (it != collidableObjects.end())
			collidableObjects.erase(it);
	}
	if (chars[3]) {
		std::vector<Serializable*>::iterator it = std::find(serializableObjects.begin(), serializableObjects.end(), dynamic_cast<Serializable*>(obj));
		if (it != serializableObjects.end())
			serializableObjects.erase(it);
	}
	if (chars[4])
		KirbyInstance = 0;

	delete[] chars;
}


bool GameLoop::loadGame(std::string fileName, bool issave, bool savecurrent) {

	if (savecurrent && currentlevel.length() != 0)
		saveGame(currentlevel+std::string(".save"));

	currentlevel = fileName;

	clear();

	Camera::getInstance().setBounds(QRectF(0, 0, 0, 0));

	std::vector<Serializable*> tempserializableObjects = Serializer::deserializeFromFile(fileName + (issave ? std::string(".save") : std::string("")));
	for (Serializable* item : tempserializableObjects) 
		addElement(dynamic_cast<GameObject*>(item));
	
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
	
	for (auto* item : this->GUIItems)
		dynamic_cast<TickableObject*>(item)->tick(deltatime);

	for (auto* item : this->particleObjects)
		if (item->shouldDelete()) {
			renderableObjects.erase(std::find(renderableObjects.begin(), renderableObjects.end(), item));
			tickableObjects.erase(std::find(tickableObjects.begin(), tickableObjects.end(), item));
			particleObjects.erase( std::find(particleObjects.begin(), particleObjects.end(), item) );
			delete item;
		}

	
	KA::Sounds::getInstance().tick(deltatime);
}

// Optional setup: Multiplayer
void GameLoop::loadNetworkData(){


}

void GameLoop::start() {
	running = true;
	//paused = false;

	pause(false);

	if(!loopthread.joinable()) loopthread = std::thread(&GameLoop::loop, this);
}


void GameLoop::pause(bool pause) {
	paused = pause;

	if (pause)
		pauseSuggestion->setTexture((TexManager::TexID)(((int)TexManager::HUD_PAUSE_POWER) + (int)(rand()%(TexManager::HUD_PAUSE_WHEEL- TexManager::HUD_PAUSE_POWER))));

	pauseGUI->setShow(pause);
	pauseSuggestion->setShow(pause);
}

void GameLoop::stop() {
	running = false;
	paused = false;
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
	
	if (e->key() == Qt::Key_H && isPressed) {
		
		hitboxenabled = !hitboxenabled;
		//loadGame(currentlevel,false,false);
		
	}

	if (e->key() == Qt::Key_J && isPressed) {
		double s = scale / scalemultiplier;
		scalemultiplier-=0.1;

		scale = s * scalemultiplier;
		scalefactor = scale * standardsize;
	}

	if (e->key() == Qt::Key_K && isPressed) {
		
		double s = scale / scalemultiplier;
		scalemultiplier+=0.1;

		scale = s * scalemultiplier;
		scalefactor = scale * standardsize;
	}

	// Pause
	if (e->key() == Qt::Key_P && isPressed) {
		
		pause(!paused); 
		
	}
	// Save
	if (e->key() == Qt::Key_K)
		GameLoop::getInstance().saveGame(currentlevel + ".edited");


	if (e->key() == Qt::Key_R)
	{
		KirbyInstance->setX(4); KirbyInstance->setY(-4);
	}


	if (e->isAutoRepeat())
		return;

	if (KirbyInstance)
		KirbyInstance->keyPressEvent(e, isPressed);
	else {
		// Controls
		if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
			Camera::getInstance().setY(Camera::getInstance().getY() + 10);
		if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() + 10);
		if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() - 10);
		if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
			Camera::getInstance().setY(Camera::getInstance().getY() - 10);
	}


	if (e->key() == Qt::Key_1 && !isPressed) {
		GameLoop::getInstance().loadGame("levels/level1");
		KA::Sounds::getInstance().play("Vegetable Valley_Theme", 0);
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
			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(k));			

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
			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(k));

		}

		//KA::Sounds::getInstance().play("Vegetable Valley_Theme");


	}

	
	//std::cout << (isPressed ? "Pressed: " : "Released: ") << e->key() << "\n";
}

std::vector<std::pair<RigidBody*, double>> GameLoop::rayCast(RigidBody* startbody, QPointF ray) {

	KA::Vec2Df testvelocity{(double)ray.x(), (double)ray.y()};

	KA::Vec2Df cp, cn;
	double ct = 0, min_t = INFINITY;
	std::vector<std::pair<RigidBody*, double>> sortedByContactTime;
	for (RigidBody* obj : collidableObjects)
		if (obj != startbody)
			if (DynamicRectVsRect(startbody->getColliderRectF(), testvelocity, obj->getColliderRectF(), cp, cn, ct))
				sortedByContactTime.push_back({ obj, ct });
	std::sort(sortedByContactTime.begin(), sortedByContactTime.end(),
		[this](const std::pair<RigidBody*, double>& a, const std::pair<RigidBody*, double>& b) {
			// if contact time is the same, give priority to nearest object
			return a.second != b.second ? a.second < b.second : pitagoricDistance(a.first->getCollider().center(), b.first->getCollider().center()) < 0;
		});

	return sortedByContactTime;

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
		[this](const std::pair<RigidBody*, double>& a, const std::pair<RigidBody*, double>& b){
			// if contact time is the same, give priority to nearest object
			return a.second != b.second ? a.second < b.second : pitagoricDistance(a.first->getCollider().center(), b.first->getCollider().center()) < 0;
		});

	return sortedByContactTime;
}
void GameLoop::clear() {
	
	//stop();

	
	
	std::thread t([]() {
		
		GameLoop::getInstance().stop();
		if (GameLoop::getInstance().loopthread.joinable())
			GameLoop::getInstance().loopthread.join();
		
		if(GameLoop::getInstance().renderableObjects.size() > 0)
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
