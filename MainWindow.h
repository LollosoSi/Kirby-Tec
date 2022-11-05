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

class MainWindow : public QMainWindow {
    Q_OBJECT


private:    
    ~MainWindow() {};

public:
    MainWindow(QGraphicsView* parent = 0);

    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* event);

    QGraphicsView* view;
    QGraphicsScene* scene;
    QRect sceneRect;

    public slots:
        void pleaseRender(std::vector<RenderableObject*>* objects, bool clearscene);
signals:
    void renderingCompleted();

};

