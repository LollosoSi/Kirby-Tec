#pragma once

#include "RenderableObject.h"
#include "TickableObject.h"
#include "TextureManager.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"

class Kirby : public RigidBody {

	Animator animator;

public:
	Kirby(const QPoint pos) : RigidBody(pos, QPoint(2.0, 1.0), 12, 14) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
	}

	Kirby() : Kirby(QPoint(0.0, 0.0)) {}


	void tick(double deltatime) {
		animator.tick(deltatime);
		RigidBody::tick(deltatime);
		//setY(getY()+(250*deltatime));

		//Camera::getInstance().goTo(QPoint(getX() - 200, getY() - 200));
	}



	//virtual QRectF getCollider() { return pm->boundingRect(); }

	void render(QGraphicsScene& scene) {
		RigidBody::render(scene);
	}
	
	QPixmap getTexture() override { return animator.getCurrentPixmap(); }

};
