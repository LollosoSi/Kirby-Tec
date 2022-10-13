#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    sceneRect = QRect(0,0,300,300);

    scene = new GraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    
    view = new QGraphicsView(scene);
    view->setGeometry(sceneRect);
    view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setMouseTracking(true);

    this->setMouseTracking(true);

    scene->setSceneRect(sceneRect);
   
    setCentralWidget(view);

    show();

    
    setWindowTitle(tr("Kirby's Adventure"));
}
        

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    // Resize drawspace here
    sceneRect.setWidth(this->width());
    sceneRect.setHeight(this->height());

    scene->setSceneRect(QRect(0,0,sceneRect.width()-5, sceneRect.height()-5));
    view->setGeometry(sceneRect);

}

void MainWindow::pleaseRender(std::vector<RenderableObject*>* renderableObjects) {
    scene->clear();
    qDeleteAll(scene->items());
    for (auto* item : *renderableObjects) item->render(*scene);
    emit(renderingCompleted());
}

void MainWindow::closeEvent(QCloseEvent* event){
    GameLoop::getInstance().stop();
}
