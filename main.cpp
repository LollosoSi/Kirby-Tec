#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QObject>

// Componenti core
#include "MainWindow.h"
#include "GameLoop.h"
#include "TextureManager.h"

#include "objects/RenderableObject.h"
#include "objects/TickableObject.h"

#include "Animator.h"
#include "Camera.h"

#include "Terrain.h"


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

		if ((rand() % 1000) < 10)
			a.playOneShot(TextureManager::getInstance().getAnimatable((rand() % 2) ? KIRBY_WALK : KIRBY_ROLL));
		


	}
	QGraphicsPixmapItem* pm = 0;
	virtual void render(QGraphicsScene& scene) {
		
		if (!pm)
			pm = scene.addPixmap(a.getCurrentPixmap());
		else
			pm->setPixmap(a.getCurrentPixmap());
		//pm->setShapeMode(QGraphicsPixmapItem::MaskShape);
		//pm->setFlag(QGraphicsItem::ItemIsMovable);
		pm->setPos(Camera::convertScreenXPos(x), Camera::convertScreenYPos(y));
		pm->setScale(4);

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

	Camera::getInstance().goTo(-100, Camera::convertY(900));

   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

	for (int i = 0; i < 700; i++) {
		Terrain* t = new Terrain(i * 16 * 4, 0);
		GameLoop::getInstance().addToRenderable(t);
	}

	for (int i = 0; i < 20; i++) {
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
	
	
 
	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	GameLoop::getInstance().start();

	//delete p;

	
    // eseguo applicazione Qt
    return a.exec();
}
