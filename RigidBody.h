#pragma once

#include "GameObject.h"
#include "TickableObject.h"
#include "RenderableObject.h"
#include "Camera.h"

#include "Vec2D.h"

#include <math.h>
#include <iostream>


#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>

enum {
	NO_COLLISION = 0,
	COLLISION_UP = 1,
	COLLISION_DOWN = 2,
	COLLISION_RIGHT = 3,
	COLLISION_LEFT = 4
};

struct Collision{
	double x = 0;
	double y = 0;
	uint8_t direction = NO_COLLISION;
};


class RigidBody : public GameObject , public TickableObject, public RenderableObject {

public:
	QPoint offset;
	QGraphicsPixmapItem* pm = 0;
	QGraphicsRectItem* hitbox = 0;

	RigidBody(const QPoint& coords, const QPoint offset, const double sizeX, const double sizeY) : GameObject(coords.x(), coords.y()) {
		this->offset = offset;
		std::cout << "Setting pos " << coords.x() << ":" << coords.y() << "\n";
		setSizeX(sizeX * scale);
		setSizeY(sizeY * scale);
		setX(x);
		setY(y);
	}
	RigidBody(const QPoint& coord, const QPoint& offset) : RigidBody(coord, offset, 16, 16) {}
	RigidBody() : RigidBody(QPoint(0.0, 0.0), QPoint(0.0, 0.0)) {}

	virtual void tick(double deltatime);
	virtual void render(QGraphicsScene& scene);
	//virtual QPixmap getTexture() = 0;

	/** Find collision, position is relative to passed object */
	//Collision findCollision(double future_x, double future_y, RigidBody& rb);

	virtual void setX(const double x) override {
		GameObject::setX(x);
		collider.setRect((offset.x() * scale) + x, getCollider().y(), getSizeX(), getSizeY());
	}

	virtual void setY(const double y) override {
		GameObject::setY(y);
		collider.setRect(getCollider().x(), (offset.y()*scale) + y, getSizeX(), getSizeY());
	}

	void setSizeX(const double sizeX) { collider.setRect(getX(), getY(), sizeX, getSizeY()); }
	void setSizeY(const double sizeY) { collider.setRect(getX(), getY(), getSizeX(), sizeY); }
	const double getSizeX() const { return collider.size().width(); }
	const double getSizeY() const { return collider.size().height(); }

	void setOffset(const QPoint of) { offset = of; }
	QPoint getOffset() const { return offset; }

	double vx = 0, vy = 100;

	virtual QRect getCollider() const { return collider; }

	virtual PB::RectF getColliderRectF() const {
		return 
			PB::RectF{ 
				PB::Vec2Df{(double)getCollider().x(), (double)getCollider().y()},
				PB::Vec2Df{(double)getSizeX(), (double)getSizeY()}
			}; 
	}

	virtual PB::Vec2Df getVelocity() const { return PB::Vec2Df{vx, vy}; }


public:
	//std::vector<Vector> vectors;
	QRect collider;
	double mass = 1;

};