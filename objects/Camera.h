#pragma once
#include "TickableObject.h"

class Camera : public TickableObject {
public:
	void tick(double delta) {

		//std::cout << "Delta" << delta << std::endl;

	}
	void setX(unsigned int x) { this->x = x; }
	void setY(unsigned int y) { this->y = y; }
	unsigned int getX() { return x; }
	unsigned int getY() { return y; }

private:
	unsigned int x = 0, y = 0;

};

