#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	if (triggerGoto) {
		numero xdist = gotoX-getX(), ydist = gotoY-getY();
		bool xinrange = abs(xdist) < 4, yinrange = abs(ydist) < 4;
		if (xinrange && yinrange)
			triggerGoto = false;
		if (!xinrange) setX(getX() + (xdist/3));
		if (!yinrange) setY(getY() + (ydist/3));
	}
}
