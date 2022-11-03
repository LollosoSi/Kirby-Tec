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


class TerrainSloped : public Terrain {

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:
	TerrainSloped(QPoint pos, objects::ObjectID id = objects::SLOPED_TERRAIN_25) : Terrain(pos, QPoint(0, 0), 62, 32) { setObjectId(id); }
	TerrainSloped(objects::ObjectID id = objects::SLOPED_TERRAIN_25) : TerrainSloped(QPoint(0, 0), id) {}
	~TerrainSloped() {}

	// Returns m in x and q in y
	QPoint getVert1() { return QPoint(getX(), getY() + ((getObjectId() == objects::SLOPED_TERRAIN_25) || (getObjectId() == objects::SLOPED_TERRAIN_45) ? getSizeY() : 0)); }
	QPoint getVert2() { return QPoint(getX() + getSizeX(), getY() + ((getObjectId() == objects::SLOPED_TERRAIN_25) || (getObjectId() == objects::SLOPED_TERRAIN_45) ? 0 : getSizeY())); }
	PB::Vec2Df getHitLine() { QPoint v1 = getVert1(), v2 = getVert2(); double m = (v2.y() - ((double)v1.y())) / (v2.x() - ((double)v1.x())); return PB::Vec2Df{ m,v1.y() - (double)(v1.x() * m) }; }

	QPixmap getTexture() override { return shouldMirror() ? TextureManager::getInstance().getAnimatable(textureId())->pixmaps[0].transformed(QTransform().scale(-1, 1)) : TextureManager::getInstance().getAnimatable(textureId())->pixmaps[0]; }

	int textureId() {
		switch (getObjectId()) {
		default:
			return TexManager::TERRAIN_SLOPED_25;
		case objects::SLOPED_TERRAIN_25:
			return TexManager::TERRAIN_SLOPED_25;
		case objects::SLOPED_TERRAIN_205:
			return TexManager::TERRAIN_SLOPED_25;
		case objects::SLOPED_TERRAIN_45:
			return TexManager::TERRAIN_SLOPED_45;
		case objects::SLOPED_TERRAIN_225:
			return TexManager::TERRAIN_SLOPED_45;
		}
	
	}
	bool shouldMirror(){

		switch (getObjectId()) {
		case objects::SLOPED_TERRAIN_25:
			return false;
		case objects::SLOPED_TERRAIN_205:
			return true;
		case objects::SLOPED_TERRAIN_45:
			return false;
		case objects::SLOPED_TERRAIN_225:
			return true;
		}
	}

	QGraphicsLineItem* qli = 0;
	void render(QGraphicsScene& scene) {

		bool visible = Camera::isVisible(getCollider());
		if (!pm && !visible)
			return;


		PB::RectF rf = getColliderRectF();

		QPen qp;
		qp.setColor(Qt::red);

		if (!pm) {
			pm = scene.addPixmap(getTexture());
			pm->setScale(scale);

			hitbox = scene.addRect(getCollider(), qp);

			QPoint c1 = Camera::worldToScreen(QPoint(getVert1().x(), getVert1().y()));
			QPoint c2 = Camera::worldToScreen(QPoint(getVert1().x() + (64 * scale), getHitLine().y + (getHitLine().x * (getVert1().x() + 64 * scale))));
			qli = scene.addLine(c1.x(), c1.y(), c2.x(), c2.y(), qp);
		}
		else if (!visible) {
			scene.removeItem(pm);
			pm = 0;

			scene.removeItem(hitbox);
			hitbox = 0;

		}

		if (pm) {
			pm->setPixmap(getTexture());
			pm->setPos(Camera::worldToScreen(QPoint(getX(), getY())));
			//pm->setRotation(renderAngles[currentDegree]);

			scene.removeItem(qli);
			QPoint c1 = Camera::worldToScreen(QPoint(getVert1().x(), getVert1().y()));
			QPoint c2 = Camera::worldToScreen(QPoint(getVert1().x() + (64 * scale), getHitLine().y + (getHitLine().x * (getVert1().x() + 64 * scale))));
			qli = scene.addLine(c1.x(), c1.y(), c2.x(), c2.y(), qp);

			QPoint p = Camera::worldToScreen(QPoint(rf.pos.x, rf.pos.y));
			scene.removeItem(hitbox);
			hitbox = scene.addRect(QRect(p.x(), p.y(), rf.size.x, rf.size.y), qp);

		}



	}
};