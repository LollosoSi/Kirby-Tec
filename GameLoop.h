#pragma once

// Debug
#include <iostream>

// Base objects
#include "TickableObject.h"
#include "RenderableObject.h"
#include "RigidBody.h"
#include "Serializable.h"
#include "Particle.h"

#include "Kirby.h"
#include "Terrain.h"

// Handle objects
#include <Vector>
#include <QTime>

// Threading
#include <thread>
#include <chrono>

// Rendering
#include <QGraphicsScene>

// Handle Keys
#include <QKeyEvent>


/** Classe GameLoop
* Responsabilita':
* loop di gioco, chiamate a tick() per ogni tickableObject registrato, render() per ogni renderableObject registrato
*
* Questa classe deve essere un Singleton
*/
class GameLoop : public QObject
{
	Q_OBJECT

public:
	// Relativi al singleton
	static GameLoop& getInstance() { static GameLoop instance; return instance; }
	~GameLoop();
	void recalculateTicks(int target_ticks);
	void recalculateFps(int target_fps);
	//

	const char obj_separator = '@';

	// Avvia / ferma loop
	void start();
	void pause();
	void stop();
	void saveGame(std::ostream& out);

	void addKirby(Kirby& kb);
	void addTerrain(Terrain& t);

	void addToTickable(TickableObject* tco);
	void addToRenderable(RenderableObject* rdo);
	void addToSerializable(Serializable* s);
	void addToCollidable(RigidBody* s);

	void addParticle(Particle *p);

	void keyPressEvent(QKeyEvent* e, bool isPressed = true);

	bool waitForThread() { loopthread.join(); return true; }

	std::vector<std::pair<RigidBody*, double>> findCollisions(RigidBody *rb);

signals:
	void pleaseRender(std::vector<RenderableObject*>* objects);

public slots:
	void renderingCompleted();

protected:
	QGraphicsScene* scene = nullptr;
	bool running = false, paused = false;

private:
	// Relativi al singleton
	GameLoop();
	GameLoop(GameLoop const&) = delete;
	void operator=(GameLoop const&) = delete;
	//

	Kirby* KirbyInstance = 0;

	// Internal calls for watchdog & methods
	void loop();
	void mergeQueues();
	void render();
	void tick(double deltatime);

	int target_ticks = 20, target_fps = 144;
	int min_delta_millis_fps = 1000 / target_fps, min_delta_millis_tick = 1000 / target_ticks;
	QTime last_millis_render, last_millis_tick, last_log;
	bool waitingForRender = false;

	std::thread loopthread;

	// Elementi da iterare
	std::vector<TickableObject*> tickableObjects;
	std::vector<RenderableObject*> renderableObjects;
	std::vector<Serializable*> serializableObjects;
	std::vector<RigidBody*> collidableObjects;
	std::vector<Particle*> particleObjects;

	// Elementi in fila
	std::vector<TickableObject*> tickableObjectsQueue;
	std::vector<RenderableObject*> renderableObjectsQueue;
	std::vector<Serializable*> serializableObjectsQueue;
	std::vector<RigidBody*> collidableObjectsQueue;

};

