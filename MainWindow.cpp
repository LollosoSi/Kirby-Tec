#include "MainWindow.h"
#include "GameLoop.h"
#include "Sprites.h"
#include <QOpenGLWidget>


using namespace std;

MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    sceneRect = QRect(0,0,aspectratio*480,480);
    setGeometry(sceneRect.x(), sceneRect.y(), sceneRect.width(), sceneRect.height());

    scene = new GraphicsScene();


    //scene->addPixmap(QPixmap("C:/Users/Edo/Desktop/Kirby-Tec/design/Map.png"));
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
    
    qgl = new QOpenGLWidget();
    qgl->setFormat(format);

    view->setViewport(qgl);

    std::cout << "Swap interval " << format.swapInterval();

    this->setMouseTracking(true);

    scene->setSceneRect(sceneRect);
   
    setCentralWidget(view);

    show();

    
    setWindowTitle(tr("Kirby's Adventure"));
   setWindowIcon(QIcon("sprites/kirbyicon.png"));
}
        

void MainWindow::resizeEvent(QResizeEvent* event) {

    //GameLoop::getInstance().pause();

    double expectedwidth = (double)(this->height() * aspectratio);
    double expectedheight = (double)(this->width() / aspectratio);

    // Resize window to avoi
    if (expectedwidth != this->width() && false) {
        event->accept();
        this->resize(QSize(expectedwidth, this->height()));

    }

    if (expectedwidth > this->width()) {
        expectedwidth = this->width();
    }
    else {
        expectedheight = this->height();
    }

    QMainWindow::resizeEvent(event);

    // Resize drawspace here
    sceneRect.setWidth(expectedwidth);
    sceneRect.setHeight(expectedheight);

    Camera::getInstance().screenwidth = expectedwidth;
    Camera::getInstance().screenheight = expectedheight;

    scene->setSceneRect(QRect(0,0,sceneRect.width()-5, sceneRect.height()-5));
    view->setGeometry(sceneRect);

    scale = ((expectedheight) / ((double)(1280.0/aspectratio))) * scalemultiplier;
    scalefactor = scale * standardsize;


    //GameLoop::getInstance().pause(false);
}

void MainWindow::pleaseRender(bool clearscene) {
   
    
    for (auto* item : GameLoop::getInstance().renderableObjects)
        item->render(*scene, clearscene);

    if (GameLoop::getInstance().renderableObjectsToBeDeleted.size() > 0) {
        for (auto* item : GameLoop::getInstance().renderableObjectsToBeDeleted)
            item->render(*scene, true);
        GameLoop::getInstance().renderableObjectsToBeDeleted.clear();
    }

    for (auto* item : GameLoop::getInstance().GUIItems)
        item->render(*scene, clearscene);

    //GameLoop::getInstance().getPauseGUI().render(*scene, clearscene);
    //GameLoop::getInstance().getPauseSuggestion().render(*scene, clearscene);
    //GameLoop::getInstance().getStartGUI().render(*scene, clearscene);


    if (scene->items().size() == 0 || clearscene) {
        scene->clear();
        qDeleteAll(scene->items());
        //qgl->update();
        //view->update();
    }

    scene->update();

    emit(renderingCompleted());
}

void MainWindow::closeEvent(QCloseEvent* event){
    this->hide();
}
