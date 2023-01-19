#pragma once

// Debug
#include <iostream>
#include <vector>

// Base objects
#include "TickableObject.h"
#include "RenderableObject.h"
#include "RigidBody.h"
#include "Serializable.h"
#include "Particle.h"

#include "Sprites.h"

#include "ObjectsHolder.h"

// Handle objects
#include <Vector>
#include <QTime>

// Threading
#include <thread>
#include <chrono>

// Rendering
#include <QGraphicsScene>
#include <QGraphicsView>

// Handle Keys
#include <QKeyEvent>

#include <QPointF>

/** Classe GameLoop
* Responsabilita':
* loop di gioco, chiamate a tick() per ogni tickableObject registrato, render() per ogni renderableObject registrato
*
* Questa classe deve essere un Singleton
*/
static bool running = false, paused = false;

class GameLoop : public QObject
{
	Q_OBJECT

private:
	std::string currentlevel = "";
	
	BaseGUI* pauseGUI;
	BaseGUI* commandsGUI;
	BaseGUI* aboutusGUI;
	BaseGUI* pauseSuggestion;
	BaseGUI* startGUI;

	BaseGUI** scoredigits;
	BaseGUI** KHealth;
	BaseGUI** LivesCounter;

	BaseGUI* view;
	BaseGUI* state;
	BaseGUI* Lives;

	bool levelblocks[1][32][23] = {
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			
		}
	};

public:
	std::thread loopthread;

	std::string		_music;
	
	std::vector<RenderableObject*> renderableObjects;
	std::vector<RenderableObject*> renderableObjectsToBeDeleted;

	std::vector<BaseGUI*> GUIItems;

	std::vector<GameObject*> deleteLater;

	void addElement(GameObject* item);
	void removeElement(GameObject* item, bool willBeDeleted = false);

	void reload();
	
	int lives = 4;
	int health = 6;
	long score = 0;
	TexID ability = HUD_POWER;

	void detachKirby() { KirbyInstance = 0; Camera::getInstance().cancelGoTo(); }

	void updateView();

	void addScore(long n) {
		setScore(getScore() + n);
	}
	void addLives(int n) {
		setLives(getLives() + n);
	}
	void setScore(int s) {
		score = s;
		updateView();
	}
	void setHealth(int h) {
		health = h;
		updateView();

	}
	void setLives(int lvs) {
		lives = lvs;
		std::cout << "New lives: " << lives << "\n";

		updateView();
	}
	void setAbility(TexID ab) {
		ability = ab;
		updateView();
	}

	long getScore() { return score; }
	int getLives() { return lives; }
	int getHealth() { return health; }

	// Relativi al singleton
	static GameLoop& getInstance() { static GameLoop instance; return instance; }
	~GameLoop();

	void recalculateTicks(int target_ticks);
	void recalculateFps(int target_fps);
	
	BaseGUI& getPauseGUI() { return *pauseGUI; }
	BaseGUI& getPauseSuggestion() { return *pauseSuggestion; }
	BaseGUI& getStartGUI() { return *startGUI; }

	GameObject* KirbyInstance = 0;

	const char obj_separator = '@';

	// Avvia / ferma loop
	void start();
	void pause(bool pause = true);
	void commands(bool pause = true);
	void aboutus(bool pause = true);
	void clear();
	static void stop();
	void saveGame(std::string fileName);
	bool loadGame(std::string fileName, bool issave = false, bool savecurrent = false);

	void playBackgroundMusicLevelBased(const std::string level);


	QPointF getKirbyPos() { return KirbyInstance ? QPointF(KirbyInstance->getX(), KirbyInstance->getY()) : QPointF(0, 0); }

	void addToTickable(TickableObject* tco);
	void addToRenderable(RenderableObject* rdo);
	void addToSerializable(Serializable* s);
	void addToCollidable(RigidBody* s);

	void addParticle(GameObject *p);

	void keyPressEvent(QKeyEvent* e, bool isPressed = true);

	std::vector<std::pair<RigidBody*, double>> findCollisions(RigidBody *rb);
	std::vector<RigidBody*> getInside(RigidBody* rb, QRectF area = QRectF(0,0,0,0));
	std::vector<std::pair<RigidBody*, double>> rayCast(RigidBody* startbody, QPointF ray);

	void showStart();

signals:
	void pleaseRender(bool clearscene);

public slots:
	void renderingCompleted();

protected:
	QGraphicsScene* scene = nullptr;
	std::atomic_bool thread_working = true;

private:
	// Relativi al singleton
	GameLoop();
	GameLoop(GameLoop const&) = delete;
	void operator=(GameLoop const&) = delete;
	//

	

	// Internal calls for watchdog & methods
	void loop();
	void mergeQueues();
	void render(bool clear = false);
	void tick(double deltatime);

	int target_ticks = 20, target_fps = 144;
	int min_delta_millis_fps = 1000 / target_fps, min_delta_millis_tick = 1000 / target_ticks;
	QTime last_millis_render, last_millis_tick, last_log;
	bool waitingForRender = false;

	void loadNetworkData();

	// Elementi da iterare
	std::vector<TickableObject*> tickableObjects;
	std::vector<Serializable*> serializableObjects;
	std::vector<RigidBody*> collidableObjects;
	std::vector<Particle*> particleObjects;
	

	// Elementi in fila
	std::vector<TickableObject*> tickableObjectsQueue;
	std::vector<RenderableObject*> renderableObjectsQueue;
	std::vector<Serializable*> serializableObjectsQueue;
	std::vector<RigidBody*> collidableObjectsQueue;

};

