#pragma once

#include "GameObject.h"
#include "TickableObject.h"
#include "RenderableObject.h"
#include "Camera.h"
#include "Serializable.h"

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

// In Degrees
//static const double renderAngles[5]{ 0, -45, -28, 45, 28};
//enum RenderDegree {
//	NO_SLOPE = 0,
//	SLOPED_45 = 1,
//	SLOPED_25 = 2,
//	SLOPED_225 = 3,
//	SLOPED_205 = 4
//};

class RigidBody : public GameObject, public TickableObject, public RenderableObject {

public:
	QPointF offset;
	QGraphicsPixmapItem* pm = 0;
	QGraphicsRectItem* hitbox = 0;


	//RenderDegree currentDegree = NO_SLOPE;
	double angle = 0;

	RigidBody(const QPointF& coords, const QPointF offset, const double sizeX, const double sizeY) : GameObject(coords.x(), coords.y()) {
		this->offset = offset;
		//std::cout << "Setting pos " << coords.x() << ":" << coords.y() << "\n";
		setSizeX(sizeX);
		setSizeY(sizeY);
		setX(x);
		setY(y);
	}
	RigidBody(const QPointF& coord, const QPointF& offset) : RigidBody(coord, offset, 16, 16) {}
	RigidBody() : RigidBody(QPointF(0.0, 0.0), QPointF(0.0, 0.0)) {}
	virtual void tick(double deltatime);
	virtual void render(QGraphicsScene& scene);
	//virtual QPixmap getTexture() = 0;
	~RigidBody() {
	
		if(pm)
		pm->setVisible(false);
		pm = 0;

		if(hitbox)
		hitbox->setVisible(false);
		hitbox = 0;

	}
	/** Find collision, position is relative to passed object */
	//Collision findCollision(double future_x, double future_y, RigidBody& rb);

	virtual void setX(const double x) override {
		GameObject::setX(x);
		collider.setRect((offset.x() / (double)scalefactor) + x, getCollider().y(), getSizeX(), getSizeY());
	}

	virtual void setY(const double y) override {
		GameObject::setY(y);
		collider.setRect(getCollider().x(), (offset.y()/(double)scalefactor) + y, getSizeX(), getSizeY());
	}

	void setSizeX(const double sizeX) { collider.setRect(getX(), getY(), sizeX, getSizeY()); }
	void setSizeY(const double sizeY) { collider.setRect(getX(), getY(), getSizeX(), sizeY); }
	const double getSizeX() const { return collider.size().width(); }
	const double getSizeY() const { return collider.size().height(); }

	void setOffset(const QPointF of) { offset = of; }
	QPointF getOffset() const { return offset; }

	KA::Vec2Df velocity{0.0, 0.0};
	KA::Vec2Df accel{0.0, 0.0};
	KA::Vec2Df lastHitNormals{ 0.0, 0.0 };

	virtual QRectF getCollider() const { return collider; }

	virtual KA::RectF getColliderRectF() const {
		return 
			KA::RectF{ 
				KA::Vec2Df{(double)getCollider().x(), (double)getCollider().y()},
				KA::Vec2Df{(double)getSizeX(), (double)getSizeY()}
			}; 
	}

	virtual KA::Vec2Df getVelocity() const { return velocity; }


public:
	//std::vector<Vector> vectors;
	QRectF collider;
	double mass = 1;

	bool isGrounded() { return ((velocity.y == 0) || (angle != 0)); }


	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << GameObject::serialize(divider) << getOffset().x() << divider << getOffset().y() << divider << getSizeX() << divider << getSizeY();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		GameObject::deserialize(start);
		setOffset(QPointF(std::atof((*(start++)).c_str()), std::atof((*(start++)).c_str())));
		setSizeX(std::atof((*(start++)).c_str()));
		setSizeY(std::atof((*(start++)).c_str()));

		return this;
	};
	
	

};