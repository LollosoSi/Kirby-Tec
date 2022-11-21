#pragma once
#include <QKeyEvent>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>

#include "GameLoop.h"

struct lastmov { int x = 0; int y = 0; };
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    lastmov lm;
    QPointF vert2;

public:
    explicit GraphicsScene(QObject* parent = 0);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    //virtual void wheelEvent(QWheelEvent* e) override;

signals:

public slots:

};

