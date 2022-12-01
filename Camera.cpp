#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	
	if (triggerGoto) {
		long double xdist = gotoXY.x() - getX(), ydist = gotoXY.y() - getY();
		bool xinrange = abs(xdist) < 0.2, yinrange = abs(ydist) < 0.2;
		if (xinrange && yinrange)
			triggerGoto = false;
		if (!xinrange) setX(getX() + (delta * pow(abs(xdist), 3) / 1.0 * (getX() > gotoXY.x() ? -1 : 1)));
		if (!yinrange) setY(getY() + (delta * pow(abs(ydist), 3) / 1.0 * (getY() > gotoXY.y() ? -1 : 1)));
		if (xdist > 20*scalefactor || ydist > 20* scalefactor) {
			// Camera was shot out!
			setX(gotoXY.x());
			setY(gotoXY.y());
		}
	}
}
