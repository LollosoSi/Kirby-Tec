#pragma once

#include <QWidget>
#include <QTimer>
#include <QPainter>

#include "RigidBody.h"
#include "Definitions.h"

#include "Animator.h"

#include "Sprites.h"

class ClickableObject {

public:
	virtual bool processClick() = 0;

};

class BaseGUI : public RigidBody, public ClickableObject {

public:
	bool show = true;

	Animator anim;

	BaseGUI(QPointF pos, TexManager::TexID id) : RigidBody(pos, QPointF(0,0), 1, 1 ) {
		anim.setAnimatable(TextureManager::getInstance().getAnimatable(id));
		setObjectId(objects::HUD);

		rigiddrawscale = 0.936;
	}

	virtual bool processClick() {
		return 0;
	}

	void tick(double delta) {
		anim.tick(delta);
	}

	QPixmap getTexture() { return anim.getCurrentPixmap(); }

	void render(QGraphicsScene& scene, bool shouldClear) override {

		

		if (!pm && !show)
			return;


		KA::RectF rf = getColliderRectF();

		QPen qp;
		qp.setColor(Qt::blue);


		if (!show || shouldClear) {
			scene.removeItem(pm);
			pm = 0;

			if (hitboxenabled) {
				scene.removeItem(hitbox);
				hitbox = 0;
			}

		}
		else if (!pm) {
			pm = scene.addPixmap(getTexture());
			pm->setZValue(1);
			if (hitboxenabled)
				hitbox = scene.addRect(getCollider(), qp);
		}



		if (pm && !shouldClear && show) {

			//std::cout << "Rendering gui\n";

			pm->setPixmap(getTexture());
			pm->setPos(Camera::fromPercentageToScreen(QPointF(getX(), getY())));
			//pm->setPos(QPointF(getX(), getY()));

			//pm->setRotation(renderAngles[currentDegree]);
			pm->setScale(scale*rigiddrawscale);

			if (hitboxenabled) {
				QPointF p = Camera::fromPercentageToScreen(QPointF(rf.pos.x, rf.pos.y));

				scene.removeItem(hitbox);
				hitbox = scene.addRect(QRect(p.x(), p.y(), rf.size.x * scalefactor, rf.size.y * scalefactor), qp);
			}

		}
	}

};

class HUD : public QWidget
{
	Q_OBJECT
private:
public:
protected slots:
};

class ScoreItem
{
private:
public:
};