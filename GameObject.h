#pragma once
#include "Definitions.h"

class GameObject {

public:
	GameObject() : GameObject(0, 0){ }
	GameObject(const double x, const double y) { setX(x); setY(y); }
	virtual const double getX() { return x; }
	virtual const double getY() { return y; }
	virtual void setX(const double x) { this->x = x; }
	virtual void setY(const double y) { this->y = y; }

protected:
	double x;
	double y;
private:

};
