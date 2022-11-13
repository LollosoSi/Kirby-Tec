#include "Definitions.h"

#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QObject>

#include <thread>

// Componenti core
#include "MainWindow.h"
#include "GameLoop.h"
#include "Camera.h"
#include "Terrain.h"
#include "Kirby.h"
#include "Sounds.h"


int main(int argc, char* argv[]) {

	// istanzio applicazione Qt
	QApplication a(argc, argv);

	MainWindow* mw = new MainWindow();

	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	
	
	/*if (!GameLoop::getInstance().loadGame("title")) {
		Terrain* t = new Terrain(objects::TERRAIN, TexManager::TITLESCREEN);
		GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
	} */
	
	
	
	
	KA::Sounds::getInstance();

	GameLoop::getInstance().start();
	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);

	if(!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)){
	
		// Show introduction
		GameLoop::getInstance().loadGame(std::string("levels/lobby"), false, false);
	}

    // eseguo applicazione Qt
    return a.exec();
}
