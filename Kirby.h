#pragma once

#include "RenderableObject.h"
#include "TickableObject.h"
#include "Sprites.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"


struct Impulse {

	KA::Vec2Df value{0,0};
	double remainingtime = 0;

};

class Kirby : public RigidBody {

	Animator animator;

protected:
	int maxwalkspeed = 8;

public:

	double kirbyscale = 0.8;

	Kirby(const QPointF pos) : RigidBody(pos, QPointF(0,0), 1 * kirbyscale, 1 * kirbyscale	) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
		setObjectId(objects::KIRBY);
		rigiddrawscale = kirbyscale;
	}



	Kirby() : Kirby(QPointF(0.0, 0.0)) {}


	virtual void setX(const double x) override {
		RigidBody::setX(x);
	}
	virtual void setY(const double y) override {
		RigidBody::setY(y);
	}

	Kirby(const Kirby& go) {
		this->setX(go.getX());
		this->setY(go.getY());
		this->setObjectId(go.getObjectId());
	}
	Cloneable* clone() const { return new Kirby(*this); }

	#define buttonsize 10
	enum {
		UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, SPACE = 4, INHALE_EXHALE = 5, INHALE_ENEMIES = 6, USE_SPECIALPWR = 7, DROP_SPECIALPWR = 8, ENTERDOOR = 9
	};
	bool buttons[buttonsize]{false};

	bool mirror = false;

	void processAcceleration();
	void processAnimation();

	Impulse jumpImpulse{ KA::Vec2Df{0,-100}, 0};

	void tick(double deltatime) {

		processAcceleration();
		processAnimation();
		animator.tick(deltatime);
		RigidBody::tick(deltatime);

		if (jumpImpulse.remainingtime != 0) {
			jumpImpulse.remainingtime -= deltatime*1000.0;
			if (jumpImpulse.remainingtime < 0)
				jumpImpulse.remainingtime = 0;
		}
	}

	int l = 0;
	void render(QGraphicsScene& scene, bool shouldClear = false) override {
		RigidBody::render(scene); 

		
	
	QPointF pos = (QPointF(getX() - 4, getY() - 4));
	//std::cout << " # " << getY() << " : " << pos.y() << (!((l++) % 10) ? "\n" : "\t");
	//Camera::getInstance().setX(pos.x());
	//Camera::getInstance().setY(pos.y());
	Camera::getInstance().goTo(pos);

	}
	
	QPixmap getTexture() override { return animator.getCurrentPixmap(mirror); }

	void keyPressEvent(QKeyEvent* e, bool isPressed) override;

};
