#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "objects/RenderableObject.h"
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

	Terrain(numero x, numero y) : RigidBody(x, y, 16, 10) {}

	QGraphicsItem* pivot;

	virtual void render(QGraphicsScene& scene) {
		if (!pm) {
			pm = scene.addPixmap(TextureManager::getInstance().getAnimatable(TERRAIN)->pixmaps[0]);
			pm->setScale(scale);
			QPen qp;
			qp.setColor(Qt::red);
			hitbox = scene.addRect(QRect(collider.x(), collider.y(), getSizeX(), getSizeY()), qp);

			QRect possignalrect = QRect(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()), 2 * scale, 2 * scale);
			pivot = scene.addEllipse(possignalrect, qp);
		}
		pm->setPos(Camera::getInstance().convertScreenXPos(getX()), Camera::getInstance().convertScreenYPos(getY()));
		hitbox->setPos(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()));
		pivot->setPos(Camera::convertScreenXPos(collider.x()), Camera::convertScreenYPos(collider.y()));

		//pm->setPos(getX(), getY());
		
	}

};