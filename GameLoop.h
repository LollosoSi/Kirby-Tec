#pragma once

// Base objects
#include "objects/TickableObject.h"
#include "objects/RenderableObject.h"

// Handle objects
#include <Vector>

// Threading
#include <thread>


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
	bool running;
	

private:
	// Relativi al singleton
	GameLoop();
	GameLoop(GameLoop const&) = delete;
	void operator=(GameLoop const&) = delete;
	//

	void loop();

	// Elementi da iterare
	std::vector<TickableObject> tickableObjects;
	std::vector<RenderableObject> renderableObjects;
	//
	

};

