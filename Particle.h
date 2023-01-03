#pragma once

#include "GameObject.h"
#include "RenderableObject.h"
#include "TickableObject.h"
#include "Animator.h"
#include "RigidBody.h"

#include "Vec2D.h"

#include <QGraphicsPixmapItem>

class Particle : public RigidBody {

protected:
	double startlifetime, lifetime, pixscale;

	QGraphicsPixmapItem* pm = 0;

public:
	Particle(QPointF start, Animatable* textureset, double lifetime = 100, double pixscale = 0.5) : RigidBody(start, QPointF(0,0), pixscale, pixscale) {
		this->pixscale = pixscale; this->lifetime = lifetime; startlifetime = lifetime;
		animator->setAnimatable(textureset);
		setZValue(5);
	}

	~Particle() {
		
	}

	Particle(const Particle& go) {
		this->setX(go.getX());
		this->setY(go.getY());
		this->setObjectId(go.getObjectId());
		this->pixscale = go.pixscale;
		this->lifetime = go.lifetime;
		this->startlifetime = go.startlifetime;
		//this->statepicker = statepicker;
	}
	Cloneable* clone() const { return new Particle(*this); }

	KA::Vec2Df movement{0, 0};

	virtual void render(QGraphicsScene& scene, bool shouldClear = false) {

		if (shouldDelete(true) || shouldClear) {
		
			if (pm) {
				scene.removeItem(pm);
				pm = 0;
			}

			return;
		
		}

		if (!pm) {
			pm = scene.addPixmap(animator->getCurrentPixmap());
			pm->setScale(pixscale * scale);
			pm->setZValue(getZValue());
		}

			pm->setPixmap(animator->getCurrentPixmap());
			pm->setPos(Camera::worldToScreen(QPointF(getX(), getY())));
		

	}

	bool shouldDelete(bool ignorepm = false) { return (lifetime <= 0) && (ignorepm || !pm); }

	virtual void tick(double delta) {

		accel.y = 9.8;
		accel.y += movement.y;
		accel.x += movement.x;


		lifetime -= delta * 1000;
		float timeindipendent = (startlifetime - lifetime) / startlifetime;

		RigidBody::tick(delta);
		animator->tick(delta);
		//setX(getX() + (movement.x * pow(M_E, timeindipendent) * delta));
		//setY(getY() + (movement.y * delta));

	}

	virtual QPixmap getTexture() { return animator->getCurrentPixmap(); }


	bool* getObjectCharacteristics() override {

		bool* characteristics = new bool[6] {
			instanceof<TickableObject, GameObject>(this),
				instanceof<RenderableObject, GameObject>(this),
				0,
				0,
				0,
				instanceof<Particle, GameObject>(this)

		};

		return characteristics;
	}

};

class Projectile : public Particle {

	objects::ObjectID* targets = 0;
	uint8_t size = 0;
	RigidBody* ignoredObject = 0;

	KA::Vec2Df customGravity{0,9.8};

public:
	Projectile(QPointF pos, KA::Vec2Df vel, Animatable* textureset, objects::ObjectID ids[], uint8_t targetsize = 0, double lifetime = 100, double pixscale = 0.5) : Particle(pos, textureset, lifetime, pixscale) {
		movement = vel;
		setTargets(ids, targetsize);
	}

	~Projectile() {
		delete[] targets;
	}

	void setCustomGravity(KA::Vec2Df vec) {
		customGravity = vec;
	}

	void setProtectedObject(RigidBody* g) {
		ignoredObject = g;
		setZValue(g->getZValue()-1);
	}

	void setTargets(objects::ObjectID ids[], uint8_t targetsize = 0) {
		if (targets)
			delete[] targets;
		this->size = targetsize;
		this->targets = new objects::ObjectID[size];
		for (int i = 0; i < size; i++)
			targets[i] = ids[i];
	
	}

	bool isTarget(objects::ObjectID id) {
		for (int i = 0; i < size; i++)
			if (targets[i]==id)
				return true;
		return false;
	}

	void tick(double delta) override;

};
