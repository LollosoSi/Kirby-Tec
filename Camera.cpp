#include "Camera.h"

#include <stdlib.h>

void Camera::tick(double delta) {
	if (triggerGoto) {
		numero xdist = gotoX - getX(), ydist = gotoY - getY();
		bool xinrange = abs(xdist) < 2, yinrange = abs(ydist) < 2;
		if (xinrange && yinrange)
			triggerGoto = false;
		else if (!xinrange) setX(getX() + (xdist / 2));
		else if (!yinrange) setX(getX() + (xdist / 2));
	}
}
