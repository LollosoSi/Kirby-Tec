#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "RenderableObject.h"
#include "GraphicsScene.h"
#include <QGraphicsPixmapItem>
#include "TextureManager.h"
#include "Camera.h"

class Terrain : public RigidBody, public RenderableObject {

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:
	Terrain() : Terrain(0, 0) {}
	~Terrain() {}

	Terrain(numero x, numero y) : RigidBody(x, y, 16, 16) {}

	QGraphicsItem* pivot;

	virtual void render(QGraphicsScene& scene) {
		QRect possignalrect = QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), 2 * scale, 2 * scale);
		QRect posrect = QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), getSizeX(), getSizeY());
		QPen qp;
		qp.setColor(Qt::red);
		if (!pm) {
			pm = scene.addPixmap(TextureManager::getInstance().getAnimatable(TERRAIN)->pixmaps[0]);
			pm->setScale(scale);
		
			hitbox = scene.addRect(posrect, qp);
			pivot = scene.addEllipse(possignalrect, qp);
		}

		scene.removeItem(hitbox);
		scene.removeItem(pivot);
		hitbox = scene.addRect(posrect,qp);
		pivot = scene.addEllipse(possignalrect,qp);

		pm->setPos(Camera::getInstance().convertScreenXPos(getX()), Camera::getInstance().convertScreenYPos(getY()));
		//hitbox->setPos(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()));
		//pivot->setPos(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()));

		//pm->setPos(getX(), getY());
		
	}

};