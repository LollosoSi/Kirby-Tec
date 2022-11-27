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
	KA::Sounds::getInstance();

	while (!TextureManager::getInstance().done) {}

	GameLoop::getInstance();

//	GameLoop::getInstance().start();
	

	//if(!GameLoop::getInstance().loadGame(std::string("levels/lobby"), true, false)){
	
		// Show introduction
	//	GameLoop::getInstance().loadGame(std::string("levels/lobby"), false, false);
	//}

	Door d(QPoint(0, 0), std::string("levels/level3"));
	d.launchAction();
	
	

	GameLoop::getInstance().recalculateTicks(60);
	GameLoop::getInstance().recalculateFps(75);

	BaseGUI view(QPointF(0, 0.757f), TexManager::HUD_VIEW);
	//BaseGUI state(QPointF(0.579f, 0.757f + (0.151f * (1-0.757f))), TexManager::HUD_BYEBYE)

	BaseGUI state(QPointF(0.578642, 0.793756), TexManager::HUD_POWER);

	
	BaseGUI* scoredigits[7]{
		new BaseGUI(QPointF(0.29,0.90422), TexManager::HUD_NUM_0),
		new BaseGUI(QPointF(0.322848, 0.90447), TexManager::HUD_NUM_1),
		new BaseGUI(QPointF(0.354305,0.90447), TexManager::HUD_NUM_2),
		new BaseGUI(QPointF(0.386589,0.90447), TexManager::HUD_NUM_3),
		new BaseGUI(QPointF(0.418046,0.90447), TexManager::HUD_NUM_4),
		new BaseGUI(QPointF(0.450331,0.90447), TexManager::HUD_NUM_5),
		new BaseGUI(QPointF(0.481788,0.90447), TexManager::HUD_NUM_6)
	};
	
	BaseGUI* KHealth[6]{
		new BaseGUI(QPointF(0.29,0.817408), TexManager::HUD_HEALTH),
		new BaseGUI(QPointF(0.322848,0.817408), TexManager::HUD_HEALTH),
		new BaseGUI(QPointF(0.354305,0.817408), TexManager::HUD_HEALTH),
		new BaseGUI(QPointF(0.386589,0.817408), TexManager::HUD_HEALTH),
		new BaseGUI(QPointF(0.418046,0.817408), TexManager::HUD_HEALTH),
		new BaseGUI(QPointF(0.450331,0.816462), TexManager::HUD_HEALTH)
	};

	BaseGUI Lives(QPointF(0.751656 , 0.849574), TexManager::HUD_LIVES);
	BaseGUI* LivesCounter[2]{
		new BaseGUI(QPointF(0.836093, 0.868496), TexManager::HUD_NUM_6),
		new BaseGUI(QPointF(0.870033,0.868496), TexManager::HUD_NUM_0)
	};

	GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(&view));
	GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(&state));

	for(auto* item : scoredigits)
		GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(item));

	for (auto* item : KHealth) {
		GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(item));
		//GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(item));
	}

	GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(&Lives));
	//GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(&Lives));

	for (auto* item : LivesCounter) {
		GameLoop::getInstance().GUIItems.push_back(dynamic_cast<RenderableObject*>(item));
		//GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(item));
	}

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


	std::cout << "Element: " << Camera::fromPercentageToScreen(QPointF(view.getX(), view.getY())).y() << "\n";
	std::cout << "Screen : " << Camera::getInstance().screenwidth << " x " << Camera::getInstance().screenheight << "\n";

    // eseguo applicazione Qt
    return a.exec();
}
