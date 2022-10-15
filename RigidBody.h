#pragma once

#include "GameObject.h"

#include <QRect>

class RigidBody : public GameObject {

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

};