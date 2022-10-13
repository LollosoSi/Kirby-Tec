#pragma once
#include <QWindow>
#include <QMainWindow>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QApplication>
#include <QStyle>
#include "objects/RenderableObject.h"


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

    // Rendering is handled inside GameLoop
    QGraphicsScene* getScene() { return this->scene; };

    public slots:
        void pleaseRender(std::vector<RenderableObject*>* objects);
    

};

