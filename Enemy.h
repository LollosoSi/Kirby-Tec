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
	EnemyID eid = WADDLEDEE;

	Animator animator;

	public:
		Enemy(QPointF coords, QPointF offset, EnemyID eid = WADDLEDEE, double sizeX = 1, double sizeY = 1) : RigidBody(coords, offset, sizeX, sizeY) {
			this->eid = eid;
			accel.x = maxwalkspeed;
			animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
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

			if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
				accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
				//velocity.x = 0;
				std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
			}

			RigidBody::tick(delta);
			
		
			mirror = velocity.x < 0;
			processAnimation();
		}

		std::string serialize(const char& divider) const override {
			std::stringstream out("", std::ios_base::app | std::ios_base::out);
			out << RigidBody::serialize(divider) << divider << eid;

			return out.str();
		}

		Serializable* deserialize(std::vector<std::string>::iterator& start) override {
			RigidBody::deserialize(start);

			eid = (EnemyID)std::atoi((*(start++)).c_str());

			return this;
		};


};