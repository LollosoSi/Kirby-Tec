#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "Vector.h"
#include "objects/TickableObject.h"

#include <QRect>


typedef uint8_t collision;
enum {
	NO_COLLISION = 0,
	COLLISION_UP = 1,
	COLLISION_DOWN = 2,
	COLLISION_RIGHT = 3,
	COLLISION_LEFT = 4
};

class RigidBody : public GameObject , public TickableObject {

	QRect collider;

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
	collision findCollision(RigidBody& rb);

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

protected:
	std::vector<Vector> vectors;

};