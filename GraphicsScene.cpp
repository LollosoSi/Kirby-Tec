#include "GraphicsScene.h"

#include "Definitions.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"

#include "Camera.h"

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

        QPointF snapped = Camera::screenToWorld(QPointF(lm.x, lm.y));
        snapped.setX((double)(floor(snapped.x()) + ( (snapped.x() - ((int)snapped.x())) > 0.4 ? 0.5 : 0)));
        snapped.setY((double)(floor(snapped.y()) ));


        Terrain* t = new Terrain(snapped, objects::STEPUP, TRANSPARENT, QPointF(0,0), 1.0, 0.2);
        GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));

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
