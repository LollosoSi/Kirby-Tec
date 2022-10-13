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
	pippo() {}


	virtual void tick(double delta) {

		x = xo + A * cos(time += delta);
		y = yo + A * sin(time += delta);

	}

	virtual void render(QGraphicsScene& scene) {
		QPen pen;
		pen.setColor(Qt::blue);
		scene.addRect(x, y, 30, 30, pen);
		
	}

private:
	int x = 0, y = 0, xo = 20, yo = 20;
	int A = 5;
	long time = 0;

};

int main(int argc, char *argv[])
{
   

    // istanzio applicazione Qt
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();

    GameLoop::getInstance().setScene(mw->getScene());
    

	// hello world
    //QPushButton* button = new QPushButton("Hello world!", mw);
    //button->show();

   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

	pippo* pippi = new pippo();

    GameLoop::getInstance().addToTickable(pippi);
	GameLoop::getInstance().addToRenderable(pippi);
 
	QObject::connect(&GameLoop::getInstance(), &GameLoop::pleaseRender, mw, &MainWindow::pleaseRender);

	GameLoop::getInstance().start();

    // eseguo applicazione Qt
    return a.exec();
}
