#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	if (triggerGoto) {
		long double xdist = gotoXY.x() - getX(), ydist = gotoXY.y() - getY();
		bool xinrange = abs(xdist) < 4, yinrange = abs(ydist) < 4;
		if (xinrange && yinrange)
			triggerGoto = false;
		if (!xinrange) setX(getX() + (delta * pow(xdist, 2) / 300 * (xdist < 0 ? -1 : 1)) );
		if (!yinrange) setY(getY() + (delta * pow(ydist, 2) / 300 * (ydist < 0 ? -1 : 1)) );
	}
}
