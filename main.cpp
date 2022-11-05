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


int main(int argc, char* argv[]) {

	// istanzio applicazione Qt
	QApplication a(argc, argv);

	MainWindow* mw = new MainWindow();

	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	
	
	if (!GameLoop::getInstance().loadGame("title")) {
		Terrain* t = new Terrain(objects::TERRAIN, TexManager::TITLESCREEN);
		GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
	}
	
	if (!GameLoop::getInstance().loadGame("testout") && false) {

		std::thread tt = std::thread([]() {
			for (int j = 0; j < 2; j++)
				for (int i = 0; i < 10; i++) {
					Terrain* t = new Terrain(QPoint(i, j));
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
				}
			}); 



		Kirby* k = new Kirby(QPoint(0.0, -100.0));
		GameLoop::getInstance().addKirby(dynamic_cast<GameObject*>(k));
		tt.join(); 
	}
	
	

	GameLoop::getInstance().start();
	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);

    // eseguo applicazione Qt
    return a.exec();
}
