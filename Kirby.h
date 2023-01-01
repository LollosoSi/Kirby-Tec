#pragma once

#include "GameObject.h"

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

protected:
	int maxwalkspeed = 5;
	uint jumpsLeft = 2;
	const int jumpCooldownDefault = 300;
	int jumpCooldown = 0;

	QGraphicsTextItem* name = 0;
	std::string sname = "";

	bool isThisTheKirbyInstance();

	int health = 6;
	const int damageCooldownDefault = 300;
	int damageCooldown = 0;


public:

	bool invincible = false;

	GameObject* storedObject = 0;

	Kirby* setName(std::string nm) { sname = nm; return this; }

	const double kirbyscale = 0.8;

	TexID status = HUD_POWER;

	double groundDistance();

	Kirby(QPointF pos = QPointF(0.0, 0.0)) : RigidBody(pos, QPointF(0, 0), 1 * kirbyscale, 1 * kirbyscale) {
		setObjectId(objects::KIRBY);
		rigiddrawscale = kirbyscale;
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
		setZValue(4);
		setSizeX(kirbyscale);
		setSizeY(kirbyscale);
	}

	Cloneable* clone() const override { return new Kirby(QPointF(getX(), getY())); }

	virtual void setX(const double x) override {
		RigidBody::setX(x);
	}
	virtual void setY(const double y) override {
		RigidBody::setY(y);
	}

	Kirby(const Kirby& go) : Kirby(QPointF(go.getX(), go.getY())) {
		setObjectId(objects::KIRBY);
	}

	const static uint8_t buttonsize = 11;
	enum KirbyKeys {
		UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, SPACE = 4, INHALE_EXHALE = 5, INHALE_ENEMIES = 6, USE_SPECIALPWR = 7, DROP_SPECIALPWR = 8, ENTERDOOR = 9, THROW_ENEMY = 10
	};
	bool buttons[buttonsize]{ false };

	bool mirror = false;

	void processAcceleration();
	void processAnimation();

	Impulse jumpImpulse{ KA::Vec2Df{0,-150}, 0 };

	void tick(double deltatime);

	int l = 0;
	void render(QGraphicsScene& scene, bool shouldClear = false) override;

	QPixmap getTexture() override {
		return animator->getCurrentPixmap((angle == 0 || !circa(velocity.x, 0.05) ? mirror : (angle < 0)));
	}

	void keyPressEvent(QKeyEvent* e, bool isPressed) override;

	static int getScoreFromObject(GameObject* item);

	void setAbility(TexID id);

	void setHealth(unsigned int v);

	int getHealth()const {return health;}

	TexID statusToAnimatable(TexID id) {
		switch (id) {
			default:
				return KIRBY_STAND;

			case HUD_CUTTER:
				return KIRBY_CUTTER;

			case HUD_SPARK:
				return KIRBY_SPARK;

			case HUD_FIRE:
				return KIRBY_FIRE;

			case HUD_BEAM:
				return KIRBY_BEAM;
		}
	
	}

};
