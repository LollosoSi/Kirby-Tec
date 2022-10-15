#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
struct lastmov { int x = 0; int y = 0; };
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    lastmov lm;

public:
    explicit GraphicsScene(QObject* parent = 0);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
signals:

public slots:

};

