#pragma once

#include <QPoint>
#include <QRect>

#include "Definitions.h"
#include "TickableObject.h"
#include "GameObject.h"

/** Questa classe e' un Singleton
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

	static QPoint worldToScreen(QPoint coord) { return QPoint((coord.x() * scale) - Camera::getInstance().getX(), (coord.y() * scale) - Camera::getInstance().getY()); }
	static QPoint screenToWorld(QPoint coord) { return QPoint((coord.x() / scale) + Camera::getInstance().getX(), (coord.y() / scale) + Camera::getInstance().getY()); }

	static bool isVisible(QRect bound) {
		return
			(
				(Camera::getInstance().getX() - (1)) <= (bound.x() + bound.width()) &&

				((Camera::getInstance().getX() + (1)) + Camera::getInstance().screenwidth) >= (bound.x())
				) &&
			((Camera::getInstance().getY() - (1)) <= (bound.y() + bound.height()) &&
				((Camera::getInstance().getY() + (1)) + Camera::getInstance().screenheight) >= (bound.y()));
	}

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

	Cloneable* clone() const {
		throw "Camera is not a cloneable object";
		return 0;
	}

};