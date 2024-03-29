#include "GameLoop.h"
#include "Vec2D.h"
#include "Camera.h"
#include "CollisionDetection.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Definitions.h"
#include "qimagereader.h"
#include "Kirby.h"
using namespace KA;
GameLoop::GameLoop() {

	QImageReader p;
	p.setAllocationLimit(0);

	GUIItems = std::vector<BaseGUI*>();
	

	pauseGUI = new BaseGUI(QPointF(0, 0), TexManager::HUD_PAUSE_SCREEN, 7);
	commandsGUI = new BaseGUI(QPointF(0, 0), TexManager::COMMANDS_HUD, 7);
	aboutusGUI = new BaseGUI(QPointF(0, 0), TexManager::ABOUTUS_HUD, 7);
	pauseSuggestion = new BaseGUI(QPointF(0.0968543, 0.0368969), TexManager::TRANSPARENT, 8);
	startGUI = new BaseGUI(QPointF(0, 0), TexManager::TITLESCREEN, 9);
	endingviewGUI = new BaseGUI(QPointF(0, 0), TexManager::FINALMESSAGE, 10);
	startGUI->setDrawScale(0.23);
	commandsGUI->setDrawScale(0.23);
	aboutusGUI->setDrawScale(0.23);
	endingviewGUI->setDrawScale(0.23);
	startGUI->playOneShot(TexManager::INTRO);
	
	

	view = new BaseGUI(QPointF(0, 0.757f), TexManager::HUD_VIEW, 6);
	state = new BaseGUI(QPointF(0.578642, 0.793756), TexManager::HUD_POWER, 6);


	scoredigits = new BaseGUI*[7]{
		new BaseGUI(QPointF(0.29,0.90422),		TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.322848,0.90447),	TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.354305,0.90447),	TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.386589,0.90447),	TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.418046,0.90447),	TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.450331,0.90447),	TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.481788,0.90447),	TexManager::HUD_NUM_0, 6)
	};

	KHealth = new BaseGUI*[6] {
		new BaseGUI(QPointF(0.29,0.817408),		TexManager::HUD_HEALTH, 6),
		new BaseGUI(QPointF(0.322848,0.817408), TexManager::HUD_HEALTH, 6),
		new BaseGUI(QPointF(0.354305,0.817408), TexManager::HUD_HEALTH, 6),
		new BaseGUI(QPointF(0.386589,0.817408), TexManager::HUD_HEALTH, 6),
		new BaseGUI(QPointF(0.418046,0.817408), TexManager::HUD_HEALTH, 6),
		new BaseGUI(QPointF(0.450331,0.816462), TexManager::HUD_HEALTH, 6)
	};

	Lives = new BaseGUI(QPointF(0.751656, 0.849574), TexManager::HUD_LIVES, 6);
	LivesCounter = new BaseGUI*[2]{
		new BaseGUI(QPointF(0.836093, 0.868496), TexManager::HUD_NUM_0, 6),
		new BaseGUI(QPointF(0.870033,0.868496), TexManager::HUD_NUM_0, 6)
	};

	GUIItems.push_back(view);
	GUIItems.push_back(state);

	for (int i = 0; i < 7; i++)
		GUIItems.push_back(scoredigits[i]);

	for (int i = 0; i < 6; i++) 
		GUIItems.push_back(KHealth[i]);
		
	GUIItems.push_back(Lives);

	for (int i = 0; i < 2; i++) 
		GUIItems.push_back(LivesCounter[i]);
		
	GUIItems.push_back(pauseGUI);
	GUIItems.push_back(pauseSuggestion);
	GUIItems.push_back(startGUI);
	GUIItems.push_back(commandsGUI);
	GUIItems.push_back(aboutusGUI);
	GUIItems.push_back(endingviewGUI);

}


void GameLoop::updateView() {

	int num = score;
	for (int i = 6; i >= 0 && num >= 0; i--) {

		int dig = num % 10;
		num = num / 10;
		if (num < 0)
			num = 0;

		scoredigits[i]->setTexture((TexManager::TexID)(TexManager::HUD_NUM_0+abs(dig)));
	}

	int num1 = lives;
	for (int i = 1; i >= 0 && num1 >= 0; i--) {

		int dig = num1 % 10;
		num1 = num1 / 10;
		if (num1 < 0)
			num1 = 0;

		LivesCounter[i]->setTexture((TexManager::TexID)(TexManager::HUD_NUM_0 + abs(dig)));
	}

	for (int i = 0; i < 6; i++) {
		KHealth[i]->setShow(health > i);
		KHealth[i]->restartAnimation();
	}
	
	this->state->setTexture(ability);

}

GameLoop::~GameLoop() {
	clear();
	stop();
	if (loopthread.joinable())
		loopthread.join();
	
	delete pauseGUI;
	delete pauseSuggestion;
	delete startGUI;
	delete commandsGUI;
	delete aboutusGUI;
	delete endingviewGUI;

	delete[] scoredigits;

	
	delete[] KHealth;

	
	delete[] LivesCounter;


}

void GameLoop::showStart() {
	startGUI->setShow(false);
	pause(true);
	pauseSuggestion->setShow(false);
	pauseGUI->setShow(false);
	commandsGUI->setShow(false);
	aboutusGUI->setShow(false);
	endingviewGUI->setShow(false);


	startGUI->setShow(true);
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

	//KA::Sounds::instance();

	QTime current = QTime::currentTime();

	int fps = 0, ticks = 0;
	last_millis_render = current, last_millis_tick = current, last_log = current;

	long deltasum = 0;
	long deltas = 0;

	int delta_tick, delta_fps, delta_log = 0;
	while (running) {
		
			current = QTime::currentTime();
			if (!waitingForRender) {
				
					if ((delta_tick = last_millis_tick.msecsTo(current)) >= min_delta_millis_tick) {
						deltas++;
						deltasum += delta_tick;

						last_millis_tick = current;
						ticks++;

						tick(timescale * delta_tick / 1000.0);

						if (!this->tickableObjectsQueue.empty() || !this->renderableObjectsQueue.empty())
							mergeQueues();

						if (deleteLater.size()>0 && !renderableObjectsToBeDeleted.size()) {
							//for (auto* item : deleteLater)
							//	delete item;
							deleteLater.clear();

						}

					}
				


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
	std::cout << "Reloading " << currentlevel << "\n";
	//loadGame(currentlevel, false, false);

		Door d(QPointF(0,0), currentlevel);
		d.savecurrent = false;
		d.launchAction();

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
	if (chars[4] && !KirbyInstance)
		KirbyInstance = obj;
	if (chars[5])
		addParticle(obj);

	delete[] chars;
}

void GameLoop::removeElement(GameObject* obj, bool willBeDeleted) {
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

	if (chars[5]) {
		std::vector<Particle*>::iterator it = std::find(particleObjects.begin(), particleObjects.end(), dynamic_cast<Particle*>(obj));
		if (it != particleObjects.end())
			particleObjects.erase(it);
	}
	

	if (willBeDeleted)
		deleteLater.push_back(obj);

	delete[] chars;
}


bool GameLoop::loadGame(std::string fileName, bool issave, bool savecurrent) {

	if (savecurrent && currentlevel.length() != 0)
		saveGame(currentlevel+std::string(".save"));

	clear();

	Camera::getInstance().setBounds(QRectF(0, 0, 0, 0));

	KirbyInstance = 0;

	std::vector<Serializable*> tempserializableObjects = Serializer::deserializeFromFile(fileName + (issave ? std::string(".save") : std::string("")));
	for (Serializable* item : tempserializableObjects) 
		addElement(dynamic_cast<GameObject*>(item));
	
	// Trigger thank you for playing
	if (currentlevel == "levels/level3" && fileName == "levels/lobby") {

		endingview(true);
		
		
		
	}

	currentlevel = fileName;

	playBackgroundMusicLevelBased(currentlevel);

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

	for (auto* item : this->GUIItems) {
		item->tick(deltatime);
	}


	if (!paused) {
		Camera::getInstance().tick(deltatime);
		for (auto* item : this->tickableObjects)
			item->tick(deltatime);

		for (auto* item : this->particleObjects)
			if (item->shouldDelete()) {
				removeElement(item, true);
			}
	}
	
}

void GameLoop::playBackgroundMusicLevelBased(const std::string level) {
	Sounds::instance()->stopSound("Lobby");
	Sounds::instance()->stopSound("Kirby_Adventure_theme");
	//Sounds::instance()->stopSound("Lobby");

	
	if (level == std::string("levels/intro"))
		Sounds::instance()->playSound("Kirby_Adventure_theme");

	if (level == std::string("levels/lobby"))
		Sounds::instance()->playSound("Lobby");
	
	if (level == std::string("levels/level1"))
		Sounds::instance()->playSound("Kirby_Adventure_theme");
	
	if (level == std::string("levels/level2"))
		Sounds::instance()->playSound("Lobby");

	if (level == std::string("levels/level3"))
		Sounds::instance()->playSound("Lobby");
	
	if (level == std::string("levels/elevator"))
		Sounds::instance()->playSound("Lobby");
	

}

// Optional setup: Multiplayer
void GameLoop::loadNetworkData(){


}

void GameLoop::start() {
	running = true;
	//paused = false;

	//Sounds::instance()->playSound("Kirby_Adventure_theme");
	startGUI->setShow(false);
	pause(false);
	//commands(false);

	if(!loopthread.joinable()) loopthread = std::thread(&GameLoop::loop, this);
}


void GameLoop::pause(bool pause) {
	paused = pause;
	
	pauseGUI->setShow(pause);
	pauseSuggestion->setShow(pause);
	if (startGUI->getShow()) {
		startGUI->setShow(false);
		//startGUI->setTexture(KIRBY_DOORS);
		TextureManager::getInstance().deleteLargeClips();
	}

	if (endingviewGUI->getShow()) {
		endingviewGUI->setShow(false);
	}
	
}

void GameLoop::commands(bool pause) {
	this->pause(pause);
	commandsGUI->setShow(pause);

}

void GameLoop::aboutus(bool pause) {
	this->pause(pause);
	aboutusGUI->setShow(pause);

}
void GameLoop::endingview(bool pause) {
	this->pause(pause);
	endingviewGUI->setShow(pause);
	
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

void GameLoop::addParticle(GameObject* p) {
	
	particleObjects.push_back(dynamic_cast<Particle*>(p));
}

void GameLoop::keyPressEvent(QKeyEvent* e, bool isPressed) {
	
	// Y H J K M N P C U L R
	if (e->key() == Qt::Key_Y && isPressed) {
	
		detachKirby();

	}

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

	if (e->key() == Qt::Key_M && isPressed)
		timescale += 0.1;
	if (e->key() == Qt::Key_N && isPressed)
		timescale -= 0.1;

	// Pause
	if (e->key() == Qt::Key_P && isPressed) {
		
		if (startGUI->getShow()) {
			pause(false);
			if (!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false))
				GameLoop::getInstance().loadGame(std::string("levels/intro"), false, false);
		} else
			pause(!paused);
		
		
	}

	// Commands
	if (e->key() == Qt::Key_C && isPressed) {

		commands(!paused);
		

	}

	if (e->key() == Qt::Key_U && isPressed) {

		aboutus(!paused);

	}
	
	// Save
	if (e->key() == Qt::Key_L && isPressed)
		GameLoop::getInstance().saveGame(currentlevel + ".edited");


	if (e->key() == Qt::Key_R && isPressed)
	{
		KirbyInstance->setX(4); KirbyInstance->setY(-4);
	}


	if (e->isAutoRepeat())
		return;

	if (KirbyInstance)
		KirbyInstance->keyPressEvent(e, isPressed);
	else if(isPressed) {
		// Controls
		if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
			Camera::getInstance().setY(Camera::getInstance().getY() + 5);
		if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() + 5);
		if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
			Camera::getInstance().setX(Camera::getInstance().getX() - 5);
		if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
			Camera::getInstance().setY(Camera::getInstance().getY() - 5);
	}


	if (e->key() == Qt::Key_1 && !isPressed) {
		Door d(QPointF(0,0), "levels/level1");
		d.launchAction();
		//GameLoop::getInstance().loadGame("levels/level1");
		
	}

	if (e->key() == Qt::Key_4 && !isPressed) {
		Door d(QPointF(0, 0), "levels/level3");
		d.launchAction();
		//GameLoop::getInstance().loadGame("levels/level1");
		
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
	
	
	stop();

	std::thread t([]() {
		
		
		if (GameLoop::getInstance().loopthread.joinable())
			GameLoop::getInstance().loopthread.join();
		
		//if(GameLoop::getInstance().renderableObjects.size() > 0)
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
