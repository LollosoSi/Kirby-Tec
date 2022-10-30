#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "RenderableObject.h"
#include "GraphicsScene.h"
#include <QGraphicsPixmapItem>
#include "TextureManager.h"
#include "Camera.h"

class Terrain : public RigidBody {

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:
	Terrain(QPoint pos, QPoint offset, int sizex, int sizey) : RigidBody(pos, offset, sizex, sizey) {
		setObjectId(objects::TERRAIN);
	}
	Terrain(QPoint pos) : Terrain(pos, QPoint(0, 0), 16, 16) {}
	Terrain() : Terrain(QPoint(0, 0)) {}
	~Terrain() {}

	QPixmap getTexture() override { return TextureManager::getInstance().getAnimatable(TERRAIN)->pixmaps[0]; }

};