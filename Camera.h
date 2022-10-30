#pragma once

#include "Definitions.h"
#include "GameObject.h"
#include "TickableObject.h"

#include <QPoint>
#include <QRect>

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
	
	void goTo(QPoint coord) {
		gotoXY = coord; triggerGoto = true; 
		//std::cout << "Going to " << gotoXY.x() << " " << gotoXY.y() << std::endl;
	}

	
	static QPoint worldToScreen(QPoint coord) { return QPoint(coord.x() - getcamera.getX(), coord.y() - getcamera.getY()); }
	static QPoint screenToWorld(QPoint coord) { return QPoint(coord.x() + getcamera.getX(), coord.y() + getcamera.getY()); }

	static bool isVisible(QRect bound) { 
		return 
			(
				(getcamera.getX() - (16 * scale) ) <= (bound.x() + bound.width()) &&

				( (getcamera.getX() + (16 * scale) ) + getcamera.screenwidth ) >= (bound.x()) 
			) && 
				( (getcamera.getY() - (16 * scale) ) <= (bound.y() + bound.height()) &&
				( ( getcamera.getY() + (16 * scale) ) + getcamera.screenheight) >= (bound.y()) ); }
	
	void tick(double delta);

	int screenwidth = 1980, screenheight = 720;

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