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

		Camera::getInstance().goTo(getX()-200, -200+Camera::convertY(getY()));
	}

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;
	QGraphicsItem* pivot = 0;

	//virtual QRectF getCollider() { return pm->boundingRect(); }
	
	void render(QGraphicsScene& scene) {
		QRect posrect = QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), getSizeX(), getSizeY());
		QRect possignalrect = QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), 2 * scale, 2 * scale);

		QPen qp;
		qp.setColor(Qt::blue);
		if (!pm) {
			pm = scene.addPixmap(animator.getCurrentPixmap());
			pm->setScale(scale);
			pm->setShapeMode(QGraphicsPixmapItem::MaskShape);
			//pm->setFlag(QGraphicsItem::ItemIsMovable);

			hitbox = scene.addRect(posrect, qp);
			pivot = scene.addEllipse(possignalrect, qp);
		}else
			pm->setPixmap(animator.getCurrentPixmap());		
		pm->setPos(Camera::convertScreenXPos(getX()), Camera::convertScreenYPos(getY()));

		//scene.removeItem(pm);
		//pm = scene.addPixmap(animator.getCurrentPixmap());
		//pm->setScale(scale);

		scene.removeItem(hitbox);
		hitbox=scene.addRect(posrect, qp);
		scene.removeItem(pivot);
		pivot = scene.addEllipse(possignalrect, qp);

		//hitbox->setX(Camera::convertScreenXPos(getCollider().x()));
		//hitbox->setY(Camera::convertScreenYPos(getCollider().y()));
		//pivot->setPos(Camera::convertScreenXPos(getCollider().x()), Camera::convertScreenYPos(getCollider().y()));

		//std::cout << "Kirby size: " << getSizeX() << " : " << getSizeY() << "\n";

	}

};
