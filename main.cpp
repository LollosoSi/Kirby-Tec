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

#include "Door.h"


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
	
	
	
	TextureManager::getInstance();
	KA::Sounds::getInstance();
	GameLoop::getInstance();

//	GameLoop::getInstance().start();
	

	//if(!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)){
	
		// Show introduction
	//	GameLoop::getInstance().loadGame(std::string("levels/lobby"), false, false);
	//}

	Door d(QPoint(0, 0), std::string("levels/lobby"));
	d.launchAction();
	
	

	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);

    // eseguo applicazione Qt
    return a.exec();
}
