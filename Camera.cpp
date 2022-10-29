#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	if (triggerGoto) {
		double xdist = gotoXY.x() - getX(), ydist = gotoXY.y() - getY();
		bool xinrange = abs(xdist) < 4, yinrange = abs(ydist) < 4;
		if (xinrange && yinrange)
			triggerGoto = false;
		if (!xinrange) setX(getX() + (xdist/30));
		if (!yinrange) setY(getY() + (ydist/30));
	}
}
