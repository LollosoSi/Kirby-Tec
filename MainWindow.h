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
#include <QCloseEvent>
#include "GameLoop.h"

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

    // Rendering is handled inside GameLoop
    QGraphicsScene* getScene() { return this->scene; };
    bool isRendering = false;

    public slots:
        void pleaseRender(std::vector<RenderableObject*>* objects);
signals:
    void renderingCompleted();

};

