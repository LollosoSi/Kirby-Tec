#pragma once

#include "RenderableObject.h"
#include "TickableObject.h"
#include "TextureManager.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"


struct Impulse {

	PB::Vec2Df value{0,0};
	double remainingtime = 0;

};

class Kirby : public RigidBody {

	Animator animator;

protected:
	int maxwalkspeed = 20;

public:
	Kirby(const QPointF pos) : RigidBody(pos, QPointF(2.0, 1.0), 12, 14) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
		setObjectId(objects::KIRBY);
	}

	Kirby() : Kirby(QPointF(0.0, 0.0)) {}

	Kirby(const Kirby& go) {
		this->setX(go.getX());
		this->setY(go.getY());
		this->setObjectId(go.getObjectId());
	}
	Cloneable* clone() const { return new Kirby(*this); }

	#define buttonsize 5
	enum {
		UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, SPACE = 4
	};
	bool buttons[buttonsize]{false};

	bool mirror = false;

	void processAcceleration();
	void processAnimation();

	Impulse jumpImpulse{ PB::Vec2Df{0,-150},0 };

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

		Camera::getInstance().goTo(Camera::worldToScreen(QPointF(getX() - (5), getY()-(5))));
	}

	//void render(QGraphicsScene& scene) { RigidBody::render(scene); }
	
	QPixmap getTexture() override { return animator.getCurrentPixmap(mirror); }

	void keyPressEvent(QKeyEvent* e, bool isPressed) override;

};
