#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "objects/TickableObject.h"
#include <math.h>

#include <iostream>

#include <QRect>


enum {
	NO_COLLISION = 0,
	COLLISION_UP = 1,
	COLLISION_DOWN = 2,
	COLLISION_RIGHT = 3,
	COLLISION_LEFT = 4
};

struct Collision{
	numero x = 0;
	numero y = 0;
	uint8_t direction = NO_COLLISION;
};

struct Point {
	numero x = 0, y = 0;
};

class customRect {
public:
	numero x = 0, y = 0;
	numero width = 0, height = 0;

	const numero getWidth() const { return width; }
	const numero getHeight() const { return height; }
	
	bool operator== (const customRect &r) {
		return (!(x - r.x) && !(y - r.y) && (getWidth() == r.getWidth()) && (getHeight() == r.getHeight()));
	}
};



class RigidBody : public GameObject , public TickableObject {

public:
	RigidBody(const numero x, const numero y, const numero sizeX, const numero sizeY) : GameObject(x,y) {
		std::cout << "Setting pos " << x << ":" << y << "\n";
		setSizeX(sizeX * scale);
		setSizeY(sizeY * scale);
		setX(x);
		setY(y);
	}
	RigidBody(const numero x, const numero y) : RigidBody(x, y, 16, 16) {}
	RigidBody() : RigidBody(0, 0) {}

	void tick(double deltatime);

	/** Find collision, position is relative to passed object */
	Collision findCollision(numero future_x, numero future_y, RigidBody& rb);

	virtual void setX(const numero x) override {
		GameObject::setX(x);
		collider.setRect(x, getY(), getSizeX(), getSizeY());
	}

	virtual void setY(const numero y) override {
		GameObject::setY(y);
		collider.setRect(getX(), y, getSizeX(), getSizeY());
	}

	void setSizeX(const numero sizeX) { collider.setRect(getX(), getY(), sizeX, getSizeY()); }
	void setSizeY(const numero sizeY) { collider.setRect(getX(), getY(), getSizeX(), sizeY); }
	const numero getSizeX() { return collider.size().width(); }
	const numero getSizeY() { return collider.size().height(); }

	bool operator==(const RigidBody &rb) {
		return collider == rb.collider;
	}
	bool operator!=(const RigidBody& rb) {
		return !((*this) == rb);
	}

	virtual QRect getCollider() { return collider; }

public:
	std::vector<Vector> vectors;
	QRect collider;
	numero mass = 1;

};