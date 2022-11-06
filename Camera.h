#pragma once

#include <QPointF>
#include <QPointF>
#include <QRect>

#include "Definitions.h"
#include "TickableObject.h"
#include "GameObject.h"

/** Notice! This object must move in screen coordinates and must have anchor in world coordinates
*
*/

/** Questa classe e' un Singleton
* Traccia le coordinate di visualizzazione
* Converte da coordinate gioco a schermo
*/
class Camera : public GameObject, public TickableObject {

public:
	// Relativi al singleton
	static Camera& getInstance() { static Camera instance; return instance; }
	~Camera() {}

	void goTo(QPointF coord) {

		gotoXY = coord; triggerGoto = true;
		//std::cout << "Going to " << gotoXY.x() << " " << gotoXY.y() << std::endl;
	}

	static QPointF worldToScreen(QPointF coord) { 
		return QPointF(
			(((double)coord.x() * (double)scalefactor) - (double)Camera::getInstance().getX()),
			(((double)coord.y() * (double)scalefactor) - (double)Camera::getInstance().getY())
		);
	}
	static QPointF screenToWorld(QPointF coord) { return QPointF(((coord.x()) + Camera::getInstance().getX())/ (double)scalefactor, ((coord.y()) + Camera::getInstance().getY())/ (double)scalefactor); }

	static bool isVisible(QRectF bound) {
		return
			(
				(Camera::getInstance().getX() - ((double)scalefactor)) <= ((bound.x()* (double)scalefactor) + (bound.width()* (double)scale)) &&

				((Camera::getInstance().getX() + ((double)scalefactor)) + Camera::getInstance().screenwidth) >= (bound.x() * (double)scalefactor)
				) &&
			((Camera::getInstance().getY() - ((double)scalefactor)) <= ((bound.y() * (double)scalefactor) + (bound.height()* (double)scale)) &&
				((Camera::getInstance().getY() + ((double)scalefactor)) + Camera::getInstance().screenheight) >= (bound.y() * (double)scalefactor));
	}

	void tick(double delta);

	int screenwidth = 1980, screenheight = 720;

protected:
	QPointF gotoXY;
	bool triggerGoto = false;

private:
	// Relativi al singleton
	Camera(Camera const&) = delete;
	Camera() : Camera(0, 0) {}
	Camera(double x, double y) : GameObject(x, y) {}
	void operator=(Camera const&) = delete;
	//

	Cloneable* clone() const {
		throw "Camera is not a cloneable object";
		return 0;
	}

};