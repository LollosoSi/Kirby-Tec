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

protected:
	bool show = true;
	Animator anim;
	std::vector<BaseGUI*> children;
	TexManager::TexID id;

public:
	
	void setShow(bool value) {
		show = value;
		//std::cout << "Setting show " << value << "\n";
	}

	void restartAnimation() {
		anim.restartAnimation();
	}

	bool getShow() const { return show; }

	BaseGUI(QPointF pos, TexManager::TexID id, uint ZValue = 2) : RigidBody(pos, QPointF(0,0), 1, 1 ) {
		setTexture(id);
		setObjectId(objects::HUD);
		setZValue(ZValue);
		rigiddrawscale = 0.936;
	}

	BaseGUI* setTexture(TexManager::TexID id) {
		this->id = id;
		anim.setAnimatable(TextureManager::getInstance().getAnimatable(id));
		return this;
	}

	virtual bool processClick() {
		return 0;
	}

	void tick(double delta) {
		if(getShow())
			anim.tick(delta);
	}

	void addChild(BaseGUI* element) {
		children.push_back(element);
	}

	void removeChild(BaseGUI* element) {
		
	}

	QPixmap getTexture() { return anim.getCurrentPixmap(); }
	void playOneShot(TexManager::TexID id) { anim.playOneShot(TextureManager::getInstance().getAnimatable(id)); }



	void render(QGraphicsScene& scene, bool shouldClear) override {

		if (show && !shouldClear) {

			QPen qp;
			qp.setColor(Qt::blue);
			KA::RectF rf = getColliderRectF();

			if (!pm) {
				pm = scene.addPixmap(getTexture());
				pm->setZValue(getZValue());
			}

			pm->setPixmap(getTexture());
			pm->setPos(Camera::fromPercentageToScreen(QPointF(getX(), getY())));
			pm->setScale(scale * rigiddrawscale * gui_scalemultiplier / scalemultiplier);

			if (hitboxenabled) {
				QPointF p = Camera::fromPercentageToScreen(QPointF(rf.pos.x, rf.pos.y));
				if (hitbox) {
					scene.removeItem(hitbox);
					delete hitbox;
				}

				hitbox = scene.addRect(QRect(p.x(), p.y(), rf.size.x * scalefactor, rf.size.y * scalefactor), qp);
			}


		}
		else if (pm) {

			scene.removeItem(pm);
			delete pm;
			pm = 0;

			if (hitbox) {
				scene.removeItem(hitbox);
				delete hitbox;
				hitbox = 0;
			}

		}
	}

};

class PauseGUI : public BaseGUI {

	PauseGUI(QPointF pos, TexManager::TexID id, uint ZValue = 2) : BaseGUI(pos, id, ZValue) {
		
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