#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QObject>


// Componenti core
#include "MainWindow.h"
#include "GameLoop.h"


#include "objects/RenderableObject.h"
#include "objects/TickableObject.h"



class pippo : public RenderableObject, public TickableObject {

public:
	QPen pen;
	

public:
	
	QPixmap qp;

	pippo() {
		int n = rand()%5;
		pen.setColor(n==0 ? Qt::blue : n == 1 ? Qt::red : n == 2 ? Qt::green : n == 3 ? Qt::magenta : Qt::yellow);
		h = (w = 5+rand()%20);
	}

	void setPix(QPixmap &p) {
		qp = p;
		
	}


	virtual void tick(double delta) {
		time += delta;
		x = xo + A * cos(2 * M_PI * f * time);
		y = yo + A * sin(2 * M_PI * f * time);
	}
	
	virtual void render(QGraphicsScene& scene) {
	
		QGraphicsPixmapItem* pm = scene.addPixmap(qp);
		pm->setPos(x, y);
		
		
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

   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

	for (int i = 0; i < 2000; i++) {
		pippo* pippi = new pippo();
		pippi->xo = 800 + rand() % 50;
		pippi->yo = 500+rand() % 50;
		pippi->f = 1.0/i;
		pippi->A = 405-i;
		pippi->setPix(*p);

		if (i < 100 || true)
			GameLoop::getInstance().addToTickable(pippi);
		else pippi->tick(0.1);
		GameLoop::getInstance().addToRenderable(pippi);
	}
 
	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);
	QObject::connect(mw, &MainWindow::renderingCompleted, &GameLoop::getInstance(), &GameLoop::renderingCompleted);

	GameLoop::getInstance().start();

	//delete p;

    // eseguo applicazione Qt
    return a.exec();
}
