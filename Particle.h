#pragma once

#include "GameObject.h"
#include "RenderableObject.h"
#include "TickableObject.h"
#include "Animator.h"

#include "Vec2D.h"

#include <QGraphicsPixmapItem>

class Particle : public GameObject, public TickableObject, public RenderableObject {

	Animator statepicker;

	double startlifetime, lifetime, pixscale;
	

	QGraphicsPixmapItem* pm = 0;

public:
	Particle(QPointF start, Animatable* textureset, double lifetime = 100, double pixscale = 0.5) : GameObject(start.x(), start.y()) {
		this->pixscale = pixscale; this->lifetime = lifetime; startlifetime = lifetime; statepicker.setAnimatable(textureset);
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
		this->statepicker = statepicker;
	}
	Cloneable* clone() const { return new Particle(*this); }

	PB::Vec2Df movement{ 2, -0.01};

	virtual void render(QGraphicsScene& scene) {

		if (shouldDelete(true)) {
		
			if (pm) {
				scene.removeItem(pm);
				pm = 0;
			}

			return;
		
		}

		if (!pm) {
			pm = scene.addPixmap(statepicker.getCurrentPixmap());
			pm->setScale(pixscale * scale);
		}

			pm->setPixmap(statepicker.getCurrentPixmap());
			pm->setPos(Camera::worldToScreen(QPointF(getX(), getY())));
		

	}

	bool shouldDelete(bool ignorepm = false) { return (lifetime <= 0) && (ignorepm || !pm); }

	virtual void tick(double delta) {
		lifetime -= delta * 1000;
		float timeindipendent = (startlifetime - lifetime) / startlifetime;

		statepicker.tick(delta);
		setX(getX() + (movement.x * pow(M_E, timeindipendent) * delta));
		setY(getY() + (movement.y * delta));

	}

	virtual QPixmap getTexture() { return statepicker.getCurrentPixmap(); }

};