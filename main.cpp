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

	GameLoop::getInstance().loadGame("filesave");

	/*
	std::thread tt = std::thread([]() {
		for (int i = 0; i < 3; i++) {
			Terrain* t = new Terrain(QPoint(i * scalefactor, (scalefactor) * (i > 300 ? cos(2 * M_PI * i / 10) : 1)));
			GameLoop::getInstance().addTerrain(*t);
		}
	});

	Kirby* k = new Kirby(QPoint(0.0, -100.0));
	GameLoop::getInstance().addKirby(*k);*/

	GameLoop::getInstance().start();
	GameLoop::getInstance().recalculateTicks(144);
	GameLoop::getInstance().recalculateFps(144);

    // eseguo applicazione Qt
    return a.exec();
}
