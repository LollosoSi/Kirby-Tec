#pragma once

#include "GameObject.h"
#include "RenderableObject.h"
#include "TickableObject.h"
#include "Animator.h"

#include "Vec2D.h"

#include <QGraphicsPixmapItem>

class Particle : public GameObject, public TickableObject, public RenderableObject {

	Animator statepicker;

	double lifetime = 100;
	

	QGraphicsPixmapItem* pm = 0;

public:
	Particle(QPoint start, double lifetime, Animatable *textureset) : GameObject(start.x(), start.y()) { this->lifetime = lifetime; statepicker.setAnimatable(textureset); }

	PB::Vec2Df movement{ 2, -0.01 * scale * 16 };

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
			pm->setScale(0.5);
		}

			pm->setPixmap(statepicker.getCurrentPixmap());
			pm->setPos(Camera::worldToScreen(QPoint(getX(), getY())));
		

	}

	bool shouldDelete(bool ignorepm = false) { return (lifetime <= 0) && (ignorepm || !pm); }

	virtual void tick(double delta) {
		lifetime -= delta * 1000;

		statepicker.tick(delta);
		setX(getX() + (movement.x * cos(rand()/100) * delta * scale * 16));
		setY(getY() + (movement.y * delta * scale * 16));

	}

	virtual QPixmap getTexture() { return statepicker.getCurrentPixmap(); }

};