#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "Vector.h"
#include "objects/TickableObject.h"

#include <QRect>


enum {
	NO_COLLISION = 0,
	COLLISION_UP = 1,
	COLLISION_DOWN = 2,
	COLLISION_RIGHT = 3,
	COLLISION_LEFT = 4
};

typedef struct Collision{
	numero x = 0;
	numero y = 0;
	uint8_t direction = NO_COLLISION;
};

typedef struct Point {
	numero x = 0, y = 0;
};



class RigidBody : public GameObject , public TickableObject {

	QRect collider;
	numero mass = 1;

public:
	RigidBody() : RigidBody(0,0) {}
	RigidBody(numero x, numero y) : RigidBody(x, y, 0, 0) {}
	RigidBody(numero x, numero y, numero sizeX, numero sizeY) : GameObject(x, y) {
		setX(getX());
		setY(getY());
		setSizeX(sizeX);
		setSizeY(sizeY);
	}

	void tick(double deltatime);

	/** Find collision, position is relative to passed object */
	Collision findCollision(numero future_x, numero future_y, RigidBody& rb);

	virtual void setX(numero x) override {
		GameObject::setX(x);
		collider.setX(x);
	}

	virtual void setY(numero y) override {
		GameObject::setY(y);
		collider.setY(y);
	}

	void setSizeX(numero sizeX) { collider.setWidth(sizeX); }
	void setSizeY(numero sizeY) { collider.setHeight(sizeY); }
	numero getSizeX() { return collider.width(); }
	numero getSizeY() { return collider.height(); }

	bool operator==(const RigidBody &rb) {
		return this->collider == rb.collider;
	}
	bool operator!=(const RigidBody& rb) {
		return !((*this) == rb);
	}

protected:
	std::vector<Vector> vectors;

};