#pragma once

#include "Definitions.h"

#include "objects/RenderableObject.h"
#include "objects/TickableObject.h"
#include "TextureManager.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"

class Kirby : public TickableObject, public RenderableObject, public RigidBody{

	Animator animator;

public:
	Kirby() : Kirby(0, 0) {}
	Kirby(const numero x, const numero y) : RigidBody(x, y) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
	}

	void tick(double deltatime) {
		animator.tick(deltatime);
		RigidBody::tick(deltatime);
	}

	QGraphicsPixmapItem* pm = 0;
	QGraphicsPixmapItem* hitbox = 0;
	void render(QGraphicsScene& scene) {
		if (!pm) {
			pm = scene.addPixmap(animator.getCurrentPixmap());
			//pm->setScale(4);
			//hitbox
		}else
			pm->setPixmap(animator.getCurrentPixmap());
		//pm->setShapeMode(QGraphicsPixmapItem::MaskShape);
		//pm->setFlag(QGraphicsItem::ItemIsMovable);
		//pm->setPos(Camera::convertScreenXPos(getX()), Camera::convertScreenYPos(getY()));
		pm->setPos(getX(), getY());
	}

};
