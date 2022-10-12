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
   

    // istanzio applicazione Qt
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();

    GameLoop::getInstance().setScene(mw->getScene());
    GameLoop::getInstance().start();

	// hello world
    //QPushButton* button = new QPushButton("Hello world!", mw);
    //button->show();

   


    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));


 

    // eseguo applicazione Qt
    return a.exec();
}
