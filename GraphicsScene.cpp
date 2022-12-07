#include "GraphicsScene.h"

#include "Definitions.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"

#include "Camera.h"
#include "Door.h"
#include "Enemy.h"

#include "ObjectsHolder.h"
#include <string>

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent) {
    //this->setBackgroundBrush(Qt::white);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}


void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    //qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    
    if (mouseEvent->button() == Qt::NoButton)
       return;


    int deltaX = (lm.x - mouseEvent->scenePos().x()), deltaY = (lm.y - mouseEvent->scenePos().y());

    //qDebug() << "DeltaX: " << deltaX << " DeltaY: " << deltaY;

    QPointF cam = Camera::worldToScreen(QPointF(Camera::getInstance().getX(), Camera::getInstance().getY()));
    QPointF snapped = Camera::screenToWorld(QPointF(cam.x() + deltaX, cam.y() + deltaY));
    

    Camera::getInstance().setX(snapped.x());
    Camera::getInstance().setY(snapped.y());
    lm.x = mouseEvent->scenePos().x();
    lm.y = mouseEvent->scenePos().y();
}

#include "Terrain.h"

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    //qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);

    if (mouseEvent->button() != Qt::MiddleButton)
        return;

    lm.x = mouseEvent->scenePos().x();
    lm.y = mouseEvent->scenePos().y();

}



void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* me) {
    //qDebug() << Q_FUNC_INFO << me->scenePos();
    QGraphicsScene::mouseReleaseEvent(me);

   // if (lm.x == me->scenePos().x() && lm.y == me->scenePos().y()) {

    lm.x = me->scenePos().x();
    lm.y = me->scenePos().y();


        std::cout << "Percentage of click coordinates: " << ((double)lm.x / (double)Camera::getInstance().screenwidth) << "% : " << ((double)lm.y / (double)Camera::getInstance().screenheight) << "\n%";
        

        QPointF snapped = Camera::screenToWorld(QPointF(lm.x, lm.y));
        snapped.setX((double)(floor(snapped.x()) + ( (snapped.x() - ((int)snapped.x())) > 0.4 ? 0.5 : 0)));
        snapped.setY((double)(floor(snapped.y()) ));


        std::cout << "Click coordinates: " << snapped.x() << " : " << snapped.y() << "\n";
        
        if (me->button() == Qt::RightButton) {
            vert2 = QPointF(snapped.x(), snapped.y());
            //Terrain* t = new Terrain(vert2);
            //GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(t));
        }
        else if (me->button() == Qt::MiddleButton) {
            //Terrain* t = new Terrain(snapped, objects::STEPUP, TRANSPARENT, QPoint(0, 0), 1, 0.3);
           // Terrain* t = new Terrain(snapped, objects::BARRIER, BARRIER_2, QPoint(0, 0), 1, 1);
            MovablePlatform* t = new MovablePlatform(snapped);
            GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(t));
        } 
        else {
            QPointF vert1 = QPointF(snapped.x(), snapped.y());
            //Terrain* t = new Terrain(snapped, objects::TERRAIN, TERRAINBLOCK, QPoint(0, 0), 1, 1);
            
            //TerrainSloped* t = new TerrainSloped(snapped, objects::SLOPED_TERRAIN, 100, 100, TRANSPARENT);
            //t->setVerts(vert1, vert2);
            static std::string r[] = { "Giovanni Muciaccia"};
            static int i = 0;
            //GameObject* t = ObjectsHolder::getInstance().getObject(objects::POPPYBROSJR);
            GameObject* t = new VectorField(vert1, QPointF(0, 0), abs(vert1.x() - vert2.x()), abs(vert1.y() - vert2.y()), KA::Vec2Df{0,-11}, 0, 1);
           // (dynamic_cast<Kirby*>(t))->setName(r[0]);
            //t->setX(snapped.x());
            //t->setY(snapped.y());

            GameLoop::getInstance().addElement(t);
        }

        

   // } 
}

void GraphicsScene::keyPressEvent(QKeyEvent* e)
{
    GameLoop::getInstance().keyPressEvent(e);
}

void GraphicsScene::keyReleaseEvent(QKeyEvent* e)
{
    GameLoop::getInstance().keyPressEvent(e, false);
}
