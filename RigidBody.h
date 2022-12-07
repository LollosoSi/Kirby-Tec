#pragma once

#include "GameObject.h"
#include "TickableObject.h"
#include "RenderableObject.h"
#include "Camera.h"
#include "Serializable.h"
#include "Sprites.h"

#include "Vec2D.h"

#include <math.h>
#include <iostream>


#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>

#include "Animator.h"

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


class VectorField;
//static void applyVectorField(RigidBody* r, VectorField* v);

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

protected:
	Animator* animator;
	

	bool damage = 0;

public:
	bool hit = 0;
	QPointF offset;
	QGraphicsPixmapItem* pm = 0;
	QGraphicsRectItem* hitbox = 0;

	double rigiddrawscale = 1;

	void doDamage() { damage = 1; }

	//RenderDegree currentDegree = NO_SLOPE;
	double angle = 0;

	RigidBody(const QPointF& coords = QPointF(0.0, 0.0), const QPointF offset = QPointF(0.0, 0.0), const double sizeX = 16, const double sizeY = 16) : GameObject(coords.x(), coords.y()) {
		animator = new Animator();

		this->offset = offset;
		//std::cout << "Setting pos " << coords.x() << ":" << coords.y() << "\n";
		setSizeX(sizeX);
		setSizeY(sizeY);
		setX(x);
		setY(y);
	}

	virtual void tick(double deltatime);
	virtual void render(QGraphicsScene& scene, bool shouldClear = false);
	GameObject* getCollidingObject(objects::ObjectID filter);
	//virtual QPixmap getTexture() = 0;
	~RigidBody() {
	
		if (animator) {
			delete animator;
			animator = 0;
		}

		if(pm)
		pm->setVisible(false);
		//delete pm;
		
		pm = 0;

		if(hitbox)
		hitbox->setVisible(false);
		//delete hitbox;
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

	void setDrawScale(double scl) { rigiddrawscale = scl; }

	bool isGrounded() { return ( (velocity.y == 0) || (angle != 0) ); }


	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << GameObject::serialize(divider) << divider << getOffset().x() << divider << getOffset().y() << divider << getSizeX() << divider << getSizeY();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		GameObject::deserialize(start);
		setOffset(QPointF(std::atof((*(start++)).c_str()), std::atof((*(start++)).c_str())));
		setSizeX(std::atof((*(start++)).c_str()));
		setSizeY(std::atof((*(start++)).c_str()));

		return this;
	}
	
	

};




class VectorField : public RigidBody {

	

protected:
	bool setVelocity, sum;
	KA::Vec2Df field;

public:
	VectorField(const QPointF& coords = QPointF(0.0, 0.0), const QPointF offset = QPointF(0.0, 0.0), const double sizeX = 16, const double sizeY = 16, KA::Vec2Df field = { 0,0 }, bool setVelocity = 0, bool doSum = 0) : RigidBody(coords, offset, sizeX, sizeY) {

		this->setObjectId(objects::VECTORFIELD);

		this->field = field;
		this->setVelocity = setVelocity;
		this->sum = doSum;

		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexID::TRANSPARENT));

	}

	bool setsVelocity() {
		return setVelocity;
	}
	bool adds() {
		return sum;
	}
	KA::Vec2Df getField() { return field; }

	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << RigidBody::serialize(divider) << divider << this->field.x << divider << this->field.y << divider << this->setVelocity << divider << this->sum;

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		RigidBody::deserialize(start);
		
		double x = std::atof((*(start++)).c_str());
		double y = std::atof((*(start++)).c_str());

		this->field = KA::Vec2Df{x,y};
		this->setVelocity = std::atoi((*(start++)).c_str());
		this->sum = std::atoi((*(start++)).c_str());

		this->setObjectId(objects::VECTORFIELD);


		return this;
	}

	QPixmap getTexture() { return animator->getCurrentPixmap(); }

	Cloneable* clone() const override { return new VectorField(); }

	// NOTICE: Pointer must be handled and deleted later
	bool* getObjectCharacteristics() override;

};


