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


// Hide console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[]) {

	// istanzio applicazione Qt
	QApplication a(argc, argv);

	TextureManager::getInstance();
	KA::Sounds::instance();

	//while (!TextureManager::getInstance().done) {}

	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);
	

	MainWindow* mw = new MainWindow();

	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	if (!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)) {
		GameLoop::getInstance().loadGame(std::string("levels/intro"), false, false);
	}

	GameLoop::getInstance().showStart();

    // eseguo applicazione Qt
    return a.exec();
}
