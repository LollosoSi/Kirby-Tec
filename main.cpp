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

#include "Sprites.h"


int main(int argc, char* argv[]) {

	// istanzio applicazione Qt
	QApplication a(argc, argv);

	MainWindow* mw = new MainWindow();

	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	
	
	/*if (!GameLoop::getInstance().loadGame("title")) {
		Terrain* t = new Terrain(objects::TERRAIN, TexManager::TITLESCREEN);
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(t));
	} */
	
	
	
	TextureManager::getInstance();
	KA::Sounds::instance();

	while (!TextureManager::getInstance().done) {}

	GameLoop::getInstance();

	//GameLoop::getInstance().start();
	

	//if(!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)){
	
		// Show introduction
	//	GameLoop::getInstance().loadGame(std::string("levels/lobby"), false, false);
	//}

	//Door d(QPoint(0, 0), std::string("levels/lobby"));
	//d.launchAction();

	if (!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)) {
		GameLoop::getInstance().loadGame(std::string("levels/intro"), false, false);
	}

	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);

	GameLoop::getInstance().showStart();

	/*
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new WaddleDee(QPointF(5+rand() % 5, -5 + rand() % 5))));
	}
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new WaddleDoo(QPointF(5+ rand() % 5, -5 + rand() % 5))));
	}
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new PoppyBrosJr(QPointF(5+ rand() % 5, -5 + rand() % 5))));
	}
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new BrontoBurt(QPointF(5+ rand() % 5, -5 + rand()%5))));
	}
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new HotHead(QPointF(5+ rand() % 5, -5 + rand() % 5))));
	}
	for (int i = 0; i < 3; i++) {
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(new Sparky(QPointF(5+ rand() % 5, -5 + rand() % 5))));
	}*/


	//std::cout << "Element: " << Camera::fromPercentageToScreen(QPointF(view.getX(), view.getY())).y() << "\n";
	//std::cout << "Screen : " << Camera::getInstance().screenwidth << " x " << Camera::getInstance().screenheight << "\n";

    // eseguo applicazione Qt
    return a.exec();
}
