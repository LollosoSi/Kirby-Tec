#include "Definitions.h"

#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QObject>

// Componenti core
#include "MainWindow.h"
#include "GameLoop.h"
#include "TextureManager.h"

#include "RenderableObject.h"
#include "TickableObject.h"

#include "Animator.h"
#include "Camera.h"

#include "Terrain.h"
#include "Kirby.h"


class pippo : public RenderableObject, public TickableObject {

public:
	Animator a;

	pippo() {
		a.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
	}


	virtual void tick(double delta) {
		a.tick(delta);
		time += delta;
		x = xo + A * cos(2 * M_PI * f * time);
		y = yo + A * sin(2 * M_PI * f * time);

		if ((rand() % 1000) < 1)
			a.playOneShot(TextureManager::getInstance().getAnimatable((rand() % 2) ? KIRBY_WALK : KIRBY_ROLL));
		


	}

	virtual QPixmap getTexture() { return a.getCurrentPixmap(); }

	QGraphicsPixmapItem* pm = 0;
	virtual void render(QGraphicsScene& scene) {
		
		if (!pm)
			pm = scene.addPixmap(getTexture());
		else
			pm->setPixmap(a.getCurrentPixmap());
		//pm->setShapeMode(QGraphicsPixmapItem::MaskShape);
		//pm->setFlag(QGraphicsItem::ItemIsMovable);
		pm->setPos(Camera::worldToScreen(QPoint(x,y)));
		pm->setScale(scale);

	}


	int x = 0, y = 0, xo = 200, yo = 200;
	int A = 100;
	double f = 1.0;
	double time = 0;
	int h = 10, w = 10;

};

QPixmap* p = NULL;

int main(int argc, char *argv[]) {

    // istanzio applicazione Qt
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();
    
	p = new QPixmap();
	if (!p->load("sprites/AI-HUD.png")) {
		std::cout << "Errore nel caricamento di immagine \n";
	}

	// hello world
    //QPushButton* button = new QPushButton("Hello world!", mw);
    //button->show();

	//Camera::getInstance().goTo(-100, Camera::convertY(900));

   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));


	for (int i = 0; i < 10; i++) {
		Terrain* t = new Terrain(QPoint(i * 16 * scale, 0+(scale*i*16)));
		
		GameLoop::getInstance().addToRenderable(t);
		GameLoop::getInstance().addToCollidable(t);
	}

	for (int i = 0; i < 1; i++) {
		pippo* pippi = new pippo();
		pippi->xo = 800/*+ rand() % 50*/;
		pippi->yo = 0;
		pippi->f = 0.5/i;
		pippi->A = 405-i;
		
		if (i < 10 || true)
			GameLoop::getInstance().addToTickable(pippi);
		else pippi->tick(0.1);
		GameLoop::getInstance().addToRenderable(pippi);
		pippi->a.playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL));
	}
 
	Kirby k = Kirby(QPoint(100.0, -100.0));

	GameLoop::getInstance().addToRenderable(&k);
	//GameLoop::getInstance().addToSerializable(&k);
	GameLoop::getInstance().addToCollidable(&k);
	GameLoop::getInstance().addToTickable(&k);
	std::cout << "Kirby pos: " << k.getX() << " : " << k.getY() << "\n";
	std::cout << "Kirby size: " << k.getSizeX() << " : " << k.getSizeY() << "\n";
	//std::cout << "Kirby collider: " << Camera::convertScreenXPos(k.getCollider().x) << " : " << Camera::convertScreenYPos(k.getCollider().y) << "\n";


	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	//QObject::connect(mw->view, &QGraphicsView::ke, &GameLoop::getInstance(), &GameLoop::keyPressEvent);

	GameLoop::getInstance().start();

	GameLoop::getInstance().recalculateTicks(144);
	GameLoop::getInstance().recalculateFps(144);

	//delete p;

    // eseguo applicazione Qt
    return a.exec();
}
