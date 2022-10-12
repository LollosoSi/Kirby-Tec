#include "MainWindow.h"



MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    sceneRect = QRect(0,0,this->width(), this->height());

    scene = new QGraphicsScene();
    
    view = new QGraphicsView(scene);
    view->setGeometry(sceneRect);
    view->setCacheMode(QGraphicsView::CacheNone);

    scene->setSceneRect(sceneRect);
   
    setCentralWidget(view);

    show();

    
   
    setWindowTitle(tr("Kirby's Adventure"));
}
        

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Resize drawspace here
    sceneRect.setWidth(this->width());
    sceneRect.setHeight(this->height());

    scene->setSceneRect(QRect(0,0,sceneRect.width()-5, sceneRect.height()-5));
    view->setGeometry(sceneRect);
   

}

MainWindow::renderObjects(std::vector<RenderableObject>* renderableObjects) {

    scene->clear();

    for (auto* item : this->renderableObjects) {
        item->render(*scene);
    }

}