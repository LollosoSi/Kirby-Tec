#pragma once
#include <QWindow>
#include <QMainWindow>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QApplication>
#include <QStyle>
#include "RenderableObject.h"
#include <QCloseEvent>
#include "GameLoop.h"
#include "GraphicsScene.h"

#include <QOpenGLWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT


private:    
    ~MainWindow() {
    
        qDeleteAll(scene->items());
        scene->clear();
    
    };

public:
    MainWindow(QGraphicsView* parent = 0);

    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* event);

    QGraphicsView* view;
    QGraphicsScene* scene;
    QOpenGLWidget* qgl;
    QRect sceneRect;

    public slots:
        void pleaseRender(bool clearscene);
signals:
    void renderingCompleted();

};

