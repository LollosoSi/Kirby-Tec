#pragma once
#include <QWindow>
#include <QMainWindow>
#include <QGraphicsView>
#include <QPainter>
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QApplication>


class MainWindow : public QMainWindow {
    Q_OBJECT

private:    
    ~MainWindow() {};

public:
    MainWindow(QGraphicsView* parent = 0);

    void resizeEvent(QResizeEvent* event);

    QGraphicsView* view;
    QGraphicsScene* scene;
    QRect sceneRect;

    public slots:
    

};

