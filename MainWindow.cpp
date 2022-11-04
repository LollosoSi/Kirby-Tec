#include "MainWindow.h"
#include "GameLoop.h"
#include <QOpenGLWidget>

using namespace std;

MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    sceneRect = QRect(0,0,aspectratio*480,480);
    setGeometry(sceneRect.x(), sceneRect.y(), sceneRect.width(), sceneRect.height());

    scene = new GraphicsScene();
    scene->setBackgroundBrush(QColor(135,206,235));
    
    view = new QGraphicsView(scene);
    view->setGeometry(sceneRect);
    view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setMouseTracking(true);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setSwapInterval(0);
    format.setRenderableType(QSurfaceFormat::OpenGL);

    format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    
    QOpenGLWidget* qgl = new QOpenGLWidget();
    qgl->setFormat(format);

    view->setViewport(qgl);

    std::cout << "Swap interval " << format.swapInterval();

    this->setMouseTracking(true);

    scene->setSceneRect(sceneRect);
   
    setCentralWidget(view);

    show();

    
    setWindowTitle(tr("Kirby's Adventure"));
}
        

void MainWindow::resizeEvent(QResizeEvent* event) {
    double expectedwidth = (double)(this->height() * aspectratio);
    double expectedheight = (double)(this->width() / aspectratio);

    if (expectedwidth != this->width()) {
        event->accept();
        this->resize(QSize(expectedwidth, this->height()));

    }

    QMainWindow::resizeEvent(event);
    // Resize drawspace here
    sceneRect.setWidth(expectedwidth);
    sceneRect.setHeight(this->height());

    

    Camera::getInstance().screenwidth = expectedwidth;
    Camera::getInstance().screenheight = this->height();

    scene->setSceneRect(QRect(0,0,sceneRect.width()-5, sceneRect.height()-5));
    view->setGeometry(sceneRect);

    

    scale = (this->height()) / (double)(895);
    scalefactor = scale * standardsize;

}

void MainWindow::pleaseRender(std::vector<RenderableObject*>* renderableObjects) {
    if(scene->items().size() == 0)
        scene->clear();
    
    //qDeleteAll(scene->items());
    for (auto* item : *renderableObjects) item->render(*scene);
    scene->update();
    emit(renderingCompleted());
}

void MainWindow::closeEvent(QCloseEvent* event){
    GameLoop::stop();
    
    this->hide();

    GameLoop::getInstance().loopthread.join();

}
