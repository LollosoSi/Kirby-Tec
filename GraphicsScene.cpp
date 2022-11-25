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

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent) {
    //this->setBackgroundBrush(Qt::white);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}


void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);

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
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);

    lm.x = mouseEvent->scenePos().x();
    lm.y = mouseEvent->scenePos().y();

}



void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* me) {
    qDebug() << Q_FUNC_INFO << me->scenePos();
    QGraphicsScene::mouseReleaseEvent(me);

    if (lm.x == me->scenePos().x() && lm.y == me->scenePos().y()) {

        std::cout << "Percentage of click coordinates: " << ((double)lm.x / (double)Camera::getInstance().screenwidth) << "% : " << ((double)lm.y / (double)Camera::getInstance().screenheight) << "\n%";

        QPointF snapped = Camera::screenToWorld(QPointF(lm.x, lm.y));
        snapped.setX((double)(floor(snapped.x()) + ( (snapped.x() - ((int)snapped.x())) > 0.4 ? 0.5 : 0)));
        snapped.setY((double)(floor(snapped.y()) ));

        
        if (me->button() == Qt::RightButton) {
            vert2 = QPointF(snapped.x(), snapped.y());
            Enemy* t = new Enemy(vert2, QPointF(0,0));
            GameLoop::getInstance().addToSerializable(dynamic_cast<GameObject*>(t));
            GameLoop::getInstance().addToCollidable(dynamic_cast<RigidBody*>(t));
            GameLoop::getInstance().addToRenderable(dynamic_cast<RenderableObject*>(t));
            GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(t));
        }
        else if (me->button() == Qt::MiddleButton) {
            //Terrain* t = new Terrain(snapped, objects::STEPUP, TRANSPARENT, QPoint(0, 0), 1, 0.3);
            Terrain* t = new Terrain(snapped, objects::BARRIER, BARRIER_2, QPoint(0, 0), 1, 1);
            GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
        } else {
            QPointF vert1 = QPointF(snapped.x(), snapped.y());
            //Terrain* t = new Terrain(snapped, objects::TERRAIN, TERRAINBLOCK, QPoint(0, 0), 1, 1);
            TerrainSloped* t = new TerrainSloped(snapped, objects::SLOPED_TERRAIN_25, 100, 100, TRANSPARENT);
            
            t->setVerts(vert1, vert2);
            //GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(t));
            GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
        }

        

    } 
}

void GraphicsScene::keyPressEvent(QKeyEvent* e)
{
    GameLoop::getInstance().keyPressEvent(e);
}

void GraphicsScene::keyReleaseEvent(QKeyEvent* e)
{
    GameLoop::getInstance().keyPressEvent(e, false);
}
