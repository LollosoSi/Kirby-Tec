#pragma once

#include "GameObject.h"
#include "RigidBody.h"
#include "objects/RenderableObject.h"
#include "GraphicsScene.h"
#include <QGraphicsPixmapItem>
#include "TextureManager.h"
#include "Camera.h"

class Terrain : public RigidBody, public RenderableObject {

	QGraphicsPixmapItem* pm = 0;

public:
	Terrain() : Terrain(0, 0) {}
	~Terrain() {}

	Terrain(numero x, numero y) : RigidBody(x, y) {}

	virtual void render(QGraphicsScene& scene) {
		if (!pm)
			pm = scene.addPixmap(TextureManager::getInstance().getAnimatable(TERRAIN)->pixmaps[0]);
		pm->setPos(Camera::getInstance().convertScreenXPos(getX()),
					Camera::getInstance().convertScreenYPos(getY()));
		pm->setScale(4);
	}

};