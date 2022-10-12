#pragma once
#include <QWindow>
#include <QGraphicsView>
#include <QPainter>


class MainWindow : public QGraphicsView {
    Q_OBJECT

public:
    MainWindow(QGraphicsView* parent = 0);

    QGraphicsScene* scene;
    QRect sceneRect;
};

