#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	if (triggerGoto) {
		long double xdist = gotoXY.x() - getX(), ydist = gotoXY.y() - getY();
		bool xinrange = abs(xdist) < 4, yinrange = abs(ydist) < 4;
		if (xinrange && yinrange)
			triggerGoto = false;
		if (!xinrange) setX(getX() + (delta * pow(xdist, 2) / 80.0 * (getX() > gotoXY.x() ? -1 : 1)));
		if (!yinrange) setY(getY() + (delta * pow(ydist, 2) / 200.0 * (getY() > gotoXY.y() ? -1 : 1)));
		if (xdist > scalefactor * 20 || ydist > scalefactor * 20) {
			// Camera was shot out!
			setX(gotoXY.x());
			setY(gotoXY.y());
		}
	}
}
