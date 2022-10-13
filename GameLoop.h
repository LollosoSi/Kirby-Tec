#pragma once

// Debug
#include <iostream>

// Base objects
#include "objects/TickableObject.h"
#include "objects/RenderableObject.h"

// Handle objects
#include <Vector>
#include <QTime>

// Threading
#include <thread>
#include <chrono>

// Rendering
#include <QGraphicsScene>


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

	

	// Avvia / ferma loop
	void start();
	void stop();
	bool running = false;

	void addToTickable(TickableObject* tco);
	void addToRenderable(RenderableObject* rdo);

signals:
	void pleaseRender(std::vector<RenderableObject*>* objects);

public slots:
	void renderingCompleted();

protected:
	QGraphicsScene* scene = nullptr;

private:
	// Relativi al singleton
	GameLoop();
	GameLoop(GameLoop const&) = delete;
	void operator=(GameLoop const&) = delete;
	//

	// Internal calls for watchdog & methods
	void loop();
	void mergeQueues();
	void render();
	void tick(double deltatime);

	int target_ticks = 20, target_fps = 120;
	int min_delta_millis_fps = 1000 / target_fps, min_delta_millis_tick = 1000 / target_ticks;
	QTime last_millis_render, last_millis_tick, last_log;
	bool waitingForRender = false;

	std::thread loopthread;

	// Elementi da iterare
	std::vector<TickableObject*> tickableObjects;
	std::vector<RenderableObject*> renderableObjects;
	// Elementi in fila
	std::vector<TickableObject*> tickableObjectsQueue;
	std::vector<RenderableObject*> renderableObjectsQueue;
	

};

