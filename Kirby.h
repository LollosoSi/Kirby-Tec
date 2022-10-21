#pragma once

#include "objects/RenderableObject.h"
#include "objects/TickableObject.h"
#include "TextureManager.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"

class Kirby : public RigidBody, public RenderableObject {

	Animator animator;

public:
	Kirby(const numero x, const numero y) : RigidBody(x, y, 16, 16) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
	}

	Kirby() : Kirby(0, 0) {}
	

	void tick(double deltatime) {
		animator.tick(deltatime);
		RigidBody::tick(deltatime);
		//setY(getY()+(250*deltatime));
	}

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

	//virtual QRectF getCollider() { return pm->boundingRect(); }
	
	void render(QGraphicsScene& scene) {
		if (!pm) {
			pm = scene.addPixmap(animator.getCurrentPixmap());
			pm->setScale(scale);
			QPen qp;
			qp.setColor(Qt::blue);
			hitbox = scene.addRect(QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), getSizeX(), getSizeY()), qp);

		}else
			pm->setPixmap(animator.getCurrentPixmap());
		//pm->setShapeMode(QGraphicsPixmapItem::MaskShape);
		//pm->setFlag(QGraphicsItem::ItemIsMovable);
		pm->setPos(Camera::convertScreenXPos(getX()), Camera::convertScreenYPos(getY()));
		//pm->setPos(getX(), getY());
		hitbox->setPos(Camera::convertScreenXPos(getCollider().x()), Camera::convertScreenYPos(getCollider().y()));

		std::cout << "Kirby size: " << getSizeX() << " : " << getSizeY() << "\n";

	}

};
