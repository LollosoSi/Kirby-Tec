#pragma once
#include "Definitions.h"

class GameObject {

public:
	GameObject() : GameObject(0, 0){ }
	GameObject(const numero x, const numero y) { setX(x); setY(y); }
	virtual const numero getX() { return x; }
	virtual const numero getY() { return y; }
	virtual void setX(const numero x) { this->x = x; }
	virtual void setY(const numero y) { this->y = y; }

protected:
	numero x;
	numero y;
private:

};
