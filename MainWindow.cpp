#include "MainWindow.h"



MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    QRect windowRect(0,0,this->width(), this->height());

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setCacheMode(QGraphicsView::CacheBackground);

    sceneRect.setX(0);
    sceneRect.setY(0);
    sceneRect.setWidth(this->width());
    sceneRect.setHeight(this->height());
    scene->setSceneRect(sceneRect);
    
    //view->show();

    QHBoxLayout* vb = new QHBoxLayout();
    vb->addItem(vb);
    this->setLayout(vb);

    

    show();

    scene->clear();
    
    QPen p(Qt::blue);
    scene->addRect(0,0,50,50, p, Qt::red);
    

    QPainter painter(view);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(windowRect, Qt::yellow);
  

    
    
    painter.setPen(p);
    painter.drawRect(10,10,100,100);

    painter.fillRect(windowRect, Qt::black);
    painter.setViewport(0,0, sceneRect.width(), sceneRect.height());
    

   // scene->clear();
   
    setWindowTitle(tr("Chip Example"));
}
        

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Resize drawspace here
    sceneRect.setWidth(this->width());
    sceneRect.setHeight(this->height());
}