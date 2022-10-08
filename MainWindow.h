#pragma once
#include <QWindow>
#include <QGraphicsView>
#include <QPainter>


class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

    QGraphicsScene* scene;

};

