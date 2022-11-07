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
			( ( ((double)coord.x() - Camera::getInstance().getX()) * (double)scalefactor)),
			( ( ((double)coord.y() - Camera::getInstance().getY()) * (double)scalefactor))
		);
	}
	static QPointF screenToWorld(QPointF coord) { return QPointF((coord.x() / (double)scalefactor) + Camera::getInstance().getX(), (coord.y() / (double)scalefactor ) + Camera::getInstance().getY()); }

	static bool isVisible(QRectF bound) {
		return
			(
				(Camera::getInstance().getX() - 1) <= (bound.x() + bound.width()) &&

				( 
					(Camera::getInstance().getX() + 1) + (Camera::getInstance().screenwidth / (double)scalefactor) >= (bound.x() * 1)
				) &&
			((Camera::getInstance().getY() - 1) <= (bound.y() + bound.height())) &&
				((Camera::getInstance().getY() + 1) + (Camera::getInstance().screenheight / (double)scalefactor)) >= (bound.y() * 1)
					
				);
	}

	void tick(double delta);

	int screenwidth = 1980, screenheight = 720;

	virtual void setX(const double x) override {
		GameObject::setX(x);
	}
	virtual void setY(const double y) override {
		GameObject::setY(y);
	}

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