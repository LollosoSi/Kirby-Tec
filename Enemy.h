#pragma once
#include "RigidBody.h"

#include "Animator.h"
#include "Sprites.h"

#include "Definitions.h"

#include "Particle.h"

enum EnemyID {
	WADDLEDEE = 1,
	WADDLEDOO = 2,
	POPPYBROSJR = 3,
	SPARKY = 4,
	HOTHEAD = 5,
	BRONTOBURT = 6
};


class Enemy : public RigidBody
{
	bool mirror = false;
	virtual void processAnimation() {

		if (!animator.isPlayingOneShot())
			if (isGrounded()) {

				if (abs(velocity.x) < 2) {

					double degang = toDegrees(angle);
					this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(
						!angle ? KIRBY_STAND :
						circa(degang, 25) ? (mirror ? KIRBY_SLOPED_25_LEFT : KIRBY_SLOPED_25) :
						circa(degang, 45) ? mirror ? KIRBY_SLOPED_45_LEFT : KIRBY_SLOPED_45 :
						circa(degang, -25) ? mirror ? KIRBY_SLOPED_25 : KIRBY_SLOPED_25_LEFT : mirror ? KIRBY_SLOPED_45 : KIRBY_SLOPED_45_LEFT
					));

				}
				else
					this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK), 0, 1.3 - abs(velocity.x / maxwalkspeed));


			}
			else {
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));

			}
	}

protected:
	double maxwalkspeed = 2;
	bool started = 0;
	

	Animator animator;

	public:
		Enemy(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), objects::ObjectID eid = objects::WADDLEDEE, double sizeX = 0.8, double sizeY = 0.8) : RigidBody(coords, offset, sizeX, sizeY) {
			this->setObjectId(eid);
			
		}
		
		QPixmap getTexture() { return animator.getCurrentPixmap(mirror); }

		void tick(double delta) override {
		
			if(!started)
				if (Camera::isVisible(getCollider()))
					started = 1;
				else
					return;

			animator.tick(delta);

			
			accel.y = 9.8;

			

			RigidBody::tick(delta);
			
		
			mirror = velocity.x > 0;
			//processAnimation();
		}

};
// enemies
class WaddleDee : public Enemy {
public:
	WaddleDee(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::WADDLEDEE, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::WADDLEDEE));
		accel.x = -maxwalkspeed;
	}

	void tick(double delta) override
{
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
		//	std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};

class WaddleDoo : public Enemy {
public:
	WaddleDoo(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::WADDLEDOO, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::WADDLEDOO));
		accel.x = -maxwalkspeed;
	}

	void tick(double delta) override
	{
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
	PoppyBrosJr(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::POPPYBROSJR, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::POPPYBROSJR));
	}

	void tick(double delta) override
	{
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
			//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};

class Sparky : public Enemy {
public:
	Sparky(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::SPARKY, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::SPARKY));
	}

	void tick(double delta) override
	{
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
			//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};

class HotHead : public Enemy {
public:
	HotHead(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0, 0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::HOTHEAD, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::HOTHEAD));
	}

	void tick(double delta) override
	{
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
			//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};

class BrontoBurt : public Enemy {
public:
	BrontoBurt(QPointF coords = QPointF(0, 0), QPointF offset = QPointF(0,0), double sizeX = 0.8, double sizeY = 0.8) : Enemy(coords, offset, objects::BRONTOBURT, sizeX, sizeY) {
		animator.setAnimatable(TextureManager::getInstance().getAnimatable(TexManager::BRONTOBURT));
	}

	void tick(double delta) override
	{
		if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
			accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
			//velocity.x = 0;
			//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
		}
		Enemy::tick(delta);
	}
};