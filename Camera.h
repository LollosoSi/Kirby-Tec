#pragma once

#include "GameObject.h"
#include <QPoint>
#include "TickableObject.h"
#include <iostream>

#define getcamera Camera::getInstance()

/** Questa classe è un Singleto
* Traccia le coordinate di visualizzazione
* Converte da coordinate gioco a schermo
*/
class Camera : public GameObject, public TickableObject {

public:
	// Relativi al singleton
	static Camera& getInstance() { static Camera instance; return instance; }
	~Camera() {}
	
	void goTo(QPoint coord) { gotoXY = coord; triggerGoto = true; std::cout << "Going to " << gotoXY.x() << " " << gotoXY.y() << std::endl; }

	
	static QPoint worldToScreen(QPoint coord) { return QPoint(coord.x() - getcamera.getX(), coord.y() - getcamera.getY()); }
	static QPoint screenToWorld(QPoint coord) { return QPoint(coord.x() + getcamera.getX(), coord.y() + getcamera.getY()); }

	void tick(double delta);

protected:
	QPoint gotoXY;
	bool triggerGoto = false;

private:
	// Relativi al singleton
	Camera(Camera const&) = delete;
	Camera() : Camera(0, 0) {}
	Camera(double x, double y) : GameObject(x, y) {}
	void operator=(Camera const&) = delete;
	//


};