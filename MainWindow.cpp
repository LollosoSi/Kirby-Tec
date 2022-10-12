#include "MainWindow.h"



MainWindow::MainWindow(QGraphicsView* parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    QRect windowRect(0,0,this->width(), this->height());
    
    this->setScene(scene);
   
    sceneRect.setX(0);
    sceneRect.setY(0);
    sceneRect.setWidth(this->width());
    sceneRect.setHeight(this->height());
    scene->setSceneRect(sceneRect);
    
    this->setCacheMode(QGraphicsView::CacheBackground);

    show();
    scene->clear();
    
    

    QPainter painter(this);

    QPen p(Qt::blue);
    
    
    painter.setPen(p);
    painter.drawRect(0,0,100,100);

   // scene->clear();
   
    setWindowTitle(tr("Chip Example"));
}
        
