#pragma once

#include "RenderableObject.h"
#include "TickableObject.h"
#include "TextureManager.h"
#include "RigidBody.h"

#include <QGraphicsPixmapItem>
#include "Camera.h"


class Kirby : public RigidBody {

	Animator animator;

public:
	Kirby(const QPoint pos) : RigidBody(pos, QPoint(2.0, 1.0), 12, 14) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
	}

	Kirby() : Kirby(QPoint(0.0, 0.0)) {}

	#define buttonsize 5
	enum {
		UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, SPACE = 4
	};
	bool buttons[buttonsize]{false};

	bool mirror = false;

	void processAcceleration();
	void processAnimation();

	void tick(double deltatime) {

		processAcceleration();
		processAnimation();
		animator.tick(deltatime);
		RigidBody::tick(deltatime);

		Camera::getInstance().goTo(QPoint(getX() - (getcamera.screenwidth/4.0), getY() - (getcamera.screenheight/2.0) ));
	}

	

	//void render(QGraphicsScene& scene) { RigidBody::render(scene); }
	
	QPixmap getTexture() override { return animator.getCurrentPixmap(mirror); }

};
