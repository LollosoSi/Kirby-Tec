#include "MainWindow.h"



MainWindow::MainWindow(QGraphicsView* parent) : QMainWindow(parent) {
    sceneRect = QRect(0,0,this->width(), this->height());

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    view->setGeometry(sceneRect);
    view->setCacheMode(QGraphicsView::CacheBackground);

    scene->setSceneRect(sceneRect);
   
    setCentralWidget(view);

    show();


   

//    QHBoxLayout* vb = new QHBoxLayout();
//    vb->addItem(vb);
 //   this->setLayout(vb);

   

    scene->clear();

    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(QPixmap("sprites/994titlescreen.png"));
    pixItem->setPos(0, 0);
    scene->addItem(pixItem);
    
    QPen p(Qt::blue);
    scene->addRect(0,0,50,50, p, Qt::red);
    

    QPainter painter(view);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(sceneRect, Qt::yellow);
    
    //std::cout << QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    
    painter.setPen(p);
    painter.drawRect(10,10,100,100);

    painter.fillRect(sceneRect, Qt::black);
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

    view->setGeometry(sceneRect);
    scene->setSceneRect(sceneRect);

}