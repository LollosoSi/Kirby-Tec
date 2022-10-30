#pragma once
#include "Definitions.h"

namespace objects {
	enum ObjectID {
		GAMEOBJECT,
		TERRAIN,
		SLOPED_TERRAIN_25,
		SLOPED_TERRAIN_45,
		KIRBY,
		CAMERA,
		PARTICLE
	};
}

class GameObject {

public:
	GameObject() : GameObject(0, 0){ }
	GameObject(const double x, const double y) { setX(x); setY(y); setObjectId(objects::GAMEOBJECT); }
	virtual const double getX() { return x; }
	virtual const double getY() { return y; }
	virtual void setX(const double x) { this->x = x; }
	virtual void setY(const double y) { this->y = y; }
	
	virtual void setObjectId(objects::ObjectID obid) { thisObjectId = obid; }
	virtual objects::ObjectID getObjectId() { return thisObjectId; }

protected:
	double x;
	double y;
	objects::ObjectID thisObjectId;


private:

};
