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
    void tick(double delta) {
    
        std::cout << "Delta" << delta << std::endl;
    
    }

    void render() {
        std::cout << "Render" << std::endl;
    }
    
};

int main(int argc, char *argv[])
{
    GameLoop::getInstance();
    GameLoop::getInstance().start();

    // istanzio applicazione Qt
    QApplication a(argc, argv);

    

    MainWindow *mw = new MainWindow();

	// hello world
    //QPushButton* button = new QPushButton("Hello world!", mw);
    //button->show();

    pippo* p = new pippo();
    int i = 0;
    while (i++ < 500) {
        p->tick(i);
        p->render();
    }
   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));


 

    // eseguo applicazione Qt
    return a.exec();
}
