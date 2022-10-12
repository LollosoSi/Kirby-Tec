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
class GameLoop
{

public:
	// Relativi al singleton
	static GameLoop& getInstance() { static GameLoop instance; return instance; }
	~GameLoop();
	//

	

	// Avvia / ferma loop
	void start();
	void stop();
	bool running = false;
	
	void setScene(QGraphicsScene* sc) { this->scene = sc; }

	void addToTickable(TickableObject* tco);
	void addToRenderable(RenderableObject* rdo);

signals:
	void pleaseRender();

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
	void tick(int deltatime);

	std::thread loopthread;

	// Elementi da iterare
	std::vector<TickableObject*> tickableObjects;
	std::vector<RenderableObject*> renderableObjects;
	// Elementi in fila
	std::vector<TickableObject*> tickableObjectsQueue;
	std::vector<RenderableObject*> renderableObjectsQueue;
	

};

