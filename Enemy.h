#pragma once
#include "RigidBody.h"

#include "Animator.h"
#include "Sprites.h"

#include "Definitions.h"

#include "Particle.h"

class Enemy : public RigidBody {
	bool mirror = false;
	virtual void processAnimation() {

		if (!animator->isPlayingOneShot())
			if (isGrounded()) {

				if (abs(velocity.x) < 2) {

					double degang = toDegrees(angle);
					this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(
						!angle ? KIRBY_STAND :
						circa(degang, 25) ? (mirror ? KIRBY_SLOPED_25_LEFT : KIRBY_SLOPED_25) :
						circa(degang, 45) ? mirror ? KIRBY_SLOPED_45_LEFT : KIRBY_SLOPED_45 :
						circa(degang, -25) ? mirror ? KIRBY_SLOPED_25 : KIRBY_SLOPED_25_LEFT : mirror ? KIRBY_SLOPED_45 : KIRBY_SLOPED_45_LEFT
					));

				}
				else
					this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK), 0, 1.3 - abs(velocity.x / maxwalkspeed));


			}
			else {
				this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));

			}
	}

protected:
	double maxwalkspeed = 2;
	bool started = 0;
	TexManager::TexID ability = TexManager::HUD_POWER;

	public:
		Enemy(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), objects::ObjectID eid = objects::WADDLEDEE, double sizeX = 1, double sizeY = 1) : RigidBody(coords, offset, sizeX, sizeY) {
			this->setObjectId(eid);
			setZValue(3);
		}
	
		void jump(double intensity = -5) { velocity.y = intensity; }

		void setStoredPower(TexManager::TexID id) { this->ability = id; }
		TexManager::TexID getStoredPower() const { return this->ability; }

		QPixmap getTexture() { return animator->getCurrentPixmap(mirror); }

		void tick(double delta) override {

			if(!started)
				if (Camera::isVisible(getCollider()))
					started = 1;
				else
					return;

			animator->tick(delta);
			RigidBody::tick(delta);
			
		
			mirror = velocity.x > 0;
			//processAnimation();
		}
		Cloneable* clone() const override { return new Enemy(*this); }
};
// enemies
class WaddleDee : public Enemy {
public:
	WaddleDee(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::WADDLEDEE, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::WADDLEDEE));
		setStoredPower(HUD_POWER);
		velocity.x = -maxwalkspeed;
	}
	Cloneable* clone() const override { return new WaddleDee(*this); }
	void tick(double delta);
};

class WaddleDoo : public Enemy {
public:
	WaddleDoo(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::WADDLEDOO, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::WADDLEDOO));
		setStoredPower(HUD_BEAM);
		accel.x = -maxwalkspeed;
	}
	Cloneable* clone() const override { return new WaddleDoo(*this); }
	void tick(double delta) override
	{
		accel.y = 9.8;
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
			//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};

class PoppyBrosJr : public Enemy {
public:
	PoppyBrosJr(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::POPPYBROSJR, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::POPPYBROSJR));
		setStoredPower(HUD_CUTTER);
	}
	Cloneable* clone() const override { return new PoppyBrosJr(*this); }
	void tick(double delta) override;

};

class Sparky : public Enemy {
public:
	Sparky(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::SPARKY, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::SPARKY));
		setStoredPower(HUD_SPARK);
	}
	Cloneable* clone() const override { return new Sparky(*this); }
	void tick(double delta);

};


class HotHead : public Enemy {
public:
	HotHead(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::HOTHEAD, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::HOTHEAD));
		setStoredPower(HUD_FIRE);
		accel.x = -maxwalkspeed;
	}
	Cloneable* clone() const override { return new HotHead(*this); }
	void tick(double delta);
};

class BrontoBurt : public Enemy {
protected:
	double time = 0;
	const double Y_accel = 3.5;
public:
	BrontoBurt(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0,0), double sizeX = 1, double sizeY = 1) : Enemy(coords, offset, objects::BRONTOBURT, sizeX, sizeY) {
		animator->setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::BRONTOBURT));
		setStoredPower(HUD_POWER);
	}
	Cloneable* clone() const override { return new BrontoBurt(*this); }
	void tick(double delta) override;
};