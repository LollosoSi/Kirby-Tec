#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent), scene(new QGraphicsScene(this)) {
    QRect windowRect(0,0,this->width(), this->height());

    show();
    QPen p(Qt::blue);
    scene->addRect(0,0,200,200, p);
   
    setWindowTitle(tr("Chip Example"));
}
        
