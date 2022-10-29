#pragma once

#include "GameObject.h"
#include "RenderableObject.h"
#include "TickableObject.h"
#include "Animator.h"

#include "Vec2D.h"

#include <QGraphicsPixmapItem>

class Particle : public GameObject, public TickableObject, public RenderableObject {

	Animator statepicker;

	int lifetime = 100;
	PB::Vec2Df movement{0, 2 * scale * 16 };

	QGraphicsPixmapItem* pm = 0;

public:
	Particle(QPoint start, int lifetime, Animatable *textureset) : GameObject(start.x(), start.y()) { this->lifetime = lifetime; statepicker.setAnimatable(textureset); }


	virtual void render(QGraphicsScene& scene) {

		if (shouldDelete(true)) {
		
			if (!pm) {
				scene.removeItem(pm);
			}

			return;
		
		}

		if (!pm) {
			pm = scene.addPixmap(statepicker.getCurrentPixmap());
			pm->setScale(0.5);
		}

		if (pm) {
			pm->setPos(Camera::worldToScreen(QPoint(getX(), getY())));
		}

	}

	bool shouldDelete(bool ignorepm = false) { return (lifetime <= 0) && (ignorepm || !pm); }

	virtual void tick(double delta) {
		lifetime -= delta;
		setX(getX() + (movement.x * delta * scale * 16));
		setY(getY() + (movement.x * delta * scale * 16));

	}

	virtual QPixmap getTexture() { return statepicker.getCurrentPixmap(); }

};