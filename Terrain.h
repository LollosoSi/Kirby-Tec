#pragma once

#include "Definitions.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "RenderableObject.h"
#include "GraphicsScene.h"
#include <QGraphicsPixmapItem>
#include "Sprites.h"
#include "Camera.h"

#include "Hud.h"

using namespace TexManager;

class Node {
protected:
	bool walkable = false;
public:
	bool isWalkable() { return walkable; }
	virtual QPointF getPos() = 0;

};

class Terrain : public RigidBody {

protected:
	TexID tid;
	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:
	Terrain(QPointF pos, QPointF offset, double sizex, double sizey, objects::ObjectID id = objects::TERRAIN, TexID tid = TERRAIN) : RigidBody(pos, offset, sizex, sizey) {
		setObjectId(id);
		this->tid = tid;
	}
	Terrain(QPointF pos, objects::ObjectID id = objects::TERRAIN, TexID tid = TERRAIN, QPointF offset = QPointF(0,0), double sizeX = 1, double sizeY = 1) : Terrain(pos, offset, sizeX, sizeY, id, tid) {}
	Terrain(objects::ObjectID id = objects::TERRAIN, TexID tid = TERRAIN) : Terrain(QPointF(0, 0), id, tid) {}
	~Terrain() {}

	QPixmap getTexture() override { return TextureManager::getInstance().getAnimatable(tid)->pixmaps[0]; }


	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << RigidBody::serialize(divider) << divider << tid;

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		RigidBody::deserialize(start);
		tid = (TexID)(std::atoi((*(start++)).c_str()));

		return this;
	};

	
};



class Background : public Terrain {

	Animator anim;

public:
	Background(QPointF pos, QPointF offset, double sizex, double sizey, objects::ObjectID id = objects::BACKGROUND, TexID tid = BACKGROUND) : Terrain(pos, offset, sizex, sizey) {
		setObjectId(id);
		this->tid = tid;
		anim.setAnimatable(TextureManager::getInstance().getAnimatable((tid)));

		Camera::getInstance().setBounds(QRectF(getX(), getY(), anim.getCurrentPixmap().width() / (double)standardsize, anim.getCurrentPixmap().height() / (double)standardsize));

		setSizeX(anim.getCurrentPixmap().width() / (double)standardsize);
		setSizeY(anim.getCurrentPixmap().height() / (double)standardsize);


	}
	Background(QPointF pos, objects::ObjectID id = objects::TERRAIN, TexID tid = TERRAIN, QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Background(pos, offset, sizeX, sizeY, id, tid) {}
	Background(objects::ObjectID id = objects::BACKGROUND, TexID tid = BACKGROUND) : Background(QPointF(0, 0), id, tid) {}
	~Background() {}

	QPixmap getTexture() override { return anim.getCurrentPixmap(); }
	virtual void tick(double delta) override {anim.tick(delta); }


	
	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << Terrain::serialize(divider);

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		Terrain::deserialize(start);

		anim.setAnimatable(TextureManager::getInstance().getAnimatable((tid)));

		
		Camera::getInstance().setBounds(QRectF(getX(), getY(), anim.getCurrentPixmap().width() / (double)standardsize, anim.getCurrentPixmap().height() / (double)standardsize));
		
		setSizeX(anim.getCurrentPixmap().width() / (double)standardsize);
		setSizeY(anim.getCurrentPixmap().height() / (double)standardsize);

		return this;
	};


};




class TerrainSloped : public Terrain {

	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:
	
	TerrainSloped(QPointF pos, objects::ObjectID id = objects::SLOPED_TERRAIN_25, double sizex = 62.0, double sizey = 32.0, TexManager::TexID texture = TERRAIN_SLOPED_25) : Terrain(pos, QPointF(0, 0), sizex, sizey, id, texture) {}
	TerrainSloped(objects::ObjectID id = objects::SLOPED_TERRAIN_25) : TerrainSloped(QPointF(0, 0), id) {}
	~TerrainSloped() {}

	QPointF vert1 = QPointF(0,0), vert2 = QPointF(0, 0);

	void setVerts(QPointF v1, QPointF v2) {
		vert1 = v1;
		vert2 = v2;
		fixverts();
		
		double hx = vert1.x() > vert2.x() ? vert1.x() : vert2.x(),
			   lx = vert1.x() < vert2.x() ? vert1.x() : vert2.x(),
			   hy = vert1.y() > vert2.y() ? vert1.y() : vert2.y(),
			   ly = vert1.y() < vert2.y() ? vert1.y() : vert2.y();
		
		setX(lx);
		setY(ly);

		collider = QRectF(lx, ly, (hx - lx), (hy - ly));

	}
	void fixverts() {
	
		if (vert1.x() > vert2.x()) {
		
			QPointF temp = vert2;
			vert2 = vert1;
			vert1 = temp;
		}
	
	}

	// Returns m in x and q in y
	QPointF getVert1() const { return vert1 != QPointF(0, 0) ? vert1 : QPointF(getX(), getY() + ((getObjectId() == objects::SLOPED_TERRAIN_25) || (getObjectId() == objects::SLOPED_TERRAIN_45) ? getSizeY() : 0)); }
	QPointF getVert2() const { return vert2 != QPointF(0, 0) ? vert2 : QPointF(getX() + getSizeX(), getY() + ((getObjectId() == objects::SLOPED_TERRAIN_25) || (getObjectId() == objects::SLOPED_TERRAIN_45) ? 0 : getSizeY())); }
	KA::Vec2Df getHitLine() {
		QPointF v1 = getVert1(), v2 = getVert2();
		double m = (v2.y() - ((double)v1.y())) / (v2.x() - ((double)v1.x()));
		return KA::Vec2Df{ m,v1.y() - (double)(v1.x() * m) };
	}

	QPixmap getTexture() override { return shouldMirror() ? TextureManager::getInstance().getAnimatable(textureId())->pixmaps[0].transformed(QTransform().scale(-1, 1)) : TextureManager::getInstance().getAnimatable(textureId())->pixmaps[0]; }

	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << Terrain::serialize(divider) << divider << vert1.x() << divider << vert1.y() << divider << vert2.x() << divider << vert2.y();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		Terrain::deserialize(start);

		double x1, y1, x2, y2;

		x1 = std::atof((*(start++)).c_str());
		y1 = std::atof((*(start++)).c_str());
		x2 = std::atof((*(start++)).c_str());
		y2 = std::atof((*(start++)).c_str());

		QPointF v1(x1,y1), v2(x2,y2);

		setVerts(v1, v2);

		return this;
	};

	int textureId() {
		if (tid == TexManager::TRANSPARENT)
			return tid;

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
		default:
			return false;
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
	void render(QGraphicsScene& scene, bool shouldClear = false) {

		//RigidBody::render(scene, shouldClear);
		
		//collider = QRectF(vert1.x(), vert1.y(), vert2.x() - vert1.x(), vert2.y() - vert1.y());

		bool visible = Camera::isVisible(getCollider());
		if ((!pm && !visible) /* || tid == TRANSPARENT */ )
			return;


		KA::RectF rf = getColliderRectF();

		QPen qp;
		qp.setColor(Qt::red);

		if (!pm) {
			pm = scene.addPixmap(getTexture());
			pm->setScale(scale);

			hitbox = scene.addRect(getCollider(), qp);

			QPointF c1 = Camera::worldToScreen(QPointF(getVert1().x(), getVert1().y()));
			QPointF c2 = Camera::worldToScreen(QPointF(getVert2().x(), getHitLine().y + (getHitLine().x * getVert2().x() )));
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
			pm->setPos(Camera::worldToScreen(QPointF(getX(), getY())));
			//pm->setRotation(renderAngles[currentDegree]);

			scene.removeItem(qli);
			QPointF c1 = Camera::worldToScreen(QPointF(getVert1().x(), getVert1().y()));
			QPointF c2 = Camera::worldToScreen(QPointF(getVert2().x(), getHitLine().y + (getHitLine().x * getVert2().x())));
			qli = scene.addLine(c1.x(), c1.y(), c2.x(), c2.y(), qp);

			QPointF p = Camera::worldToScreen(QPointF(rf.pos.x, rf.pos.y));
			scene.removeItem(hitbox);
			hitbox = scene.addRect(QRect(p.x(), p.y(), rf.size.x * scalefactor, rf.size.y * scalefactor), qp);

		}



	}
};



class MovablePlatform : public Terrain {

protected:
	TexID tid;
	QGraphicsPixmapItem* pm = 0;
	QGraphicsItem* hitbox = 0;

public:

	double time = 0, omega = 2 * M_PI * 0.2;
	QPointF startpos;

	MovablePlatform(QPointF pos, QPointF offset, double sizex, double sizey, objects::ObjectID id = objects::PLATFORM, TexID tid = TERRAIN) : Terrain(pos, offset, sizex, sizey) {
		setObjectId(id);
		this->tid = tid;
		startpos = pos;
	}
	MovablePlatform(QPointF pos, objects::ObjectID id = objects::PLATFORM, TexID tid = TERRAIN, QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : MovablePlatform(pos, offset, sizeX, sizeY, id, tid) {}
	MovablePlatform(objects::ObjectID id = objects::PLATFORM, TexID tid = TERRAIN) : MovablePlatform(QPointF(0, 0), id, tid) {}
	~MovablePlatform() {}

	QPixmap getTexture() override { return TextureManager::getInstance().getAnimatable(tid)->pixmaps[0]; }

	void tick(double delta) override {
		time += delta;
		setY(startpos.y() + (sin(omega*time)));
	}

	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << Terrain::serialize(divider) << divider << startpos.x() << divider << startpos.y();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		Terrain::deserialize(start);
		startpos = QPointF(std::atof((*(start++)).c_str()), std::atof((*(start++)).c_str()));

		return this;
	};


};