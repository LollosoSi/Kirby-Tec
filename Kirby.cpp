#include "Kirby.h"
#include "Sounds.h"
#include "GameLoop.h"
#include "Particle.h"

#include "Door.h"

void Kirby::processAcceleration() {

	if (getY() > 15) {
		std::thread t(
			[]() {
				GameLoop::getInstance().reload(); 
			}
		);
		t.detach();
		return;
	}

	KA::Vec2Df temp{ 0.0, 9.8 };

	if (buttons[RIGHT] ^ buttons[LEFT]) {
		if (buttons[RIGHT] && (velocity.x < maxwalkspeed) ) {
			mirror = false;
			temp.x += (maxwalkspeed*2) * (1 - abs(velocity.x / maxwalkspeed)) * (velocity.x < 0 ? 2 : 1);
		}

		if (buttons[LEFT] && (velocity.x > -maxwalkspeed) ) {
			mirror = true;
			temp.x -= (maxwalkspeed*2) * (1 - abs(velocity.x / maxwalkspeed)) * (velocity.x > 0 ? 2 : 1);
		}
	} else if (isGrounded()) {
		if(abs(velocity.x) > 0.3)
			temp.x = ((velocity.x > 0 ? -1 : 1) * 9.8 * 3);
		else if(abs(velocity.x) > 0)
			velocity.x = 0;
		
		
	}

	if (buttons[DOWN]) {

	}

	if (isGrounded())
		jumpsLeft = 2;

	/*
	if ((currentDegree != NO_SLOPE) && false) {
		PB::Vec2Df rot = temp;
		double rad = toRadians(renderAngles[currentDegree]);
		rot.x = (temp.x * cos(rad)) - (temp.y * sin(rad));
		rot.y = (temp.x * sin(rad)) + (temp.y * cos(rad));
		temp = rot;
	}
	*/


	if (buttons[SPACE] && (lastHitNormals.y < 0) && (jumpImpulse.remainingtime == 0) && jumpsLeft > 0 && jumpCooldown == 0) {
		//buttons[SPACE] = false;
		jumpsLeft--;
		jumpCooldown = jumpCooldownDefault;
		/* This acceleration must be great velocity in the deltatime frame, usually around 0.001 s */
		jumpImpulse.remainingtime += 30;
		KA::Sounds::getInstance().play("jump");
		this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		this->animator.playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL), 0);
	}


	if (jumpImpulse.remainingtime > 0) {
		//temp += jumpImpulse.value;
		velocity += jumpImpulse.value * (jumpImpulse.remainingtime/1000.0);
		jumpImpulse.remainingtime = 0;

		angle = 0;
		//currentDegree = NO_SLOPE;
	}

	this->accel = temp;
	
}


void Kirby::processAnimation() {

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
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK), 0, 1.3-abs(velocity.x / maxwalkspeed));

			if (!(buttons[RIGHT] ^ buttons[LEFT]) && (velocity.mag() > 1)) {
				if (!(rand() % 2)) {
					Particle *p = new Particle(QPointF(getX() + ((getSizeX() / 5) * ((rand() % 5) + 1)), getY() + getSizeY()), TextureManager::getInstance().getAnimatable(PARTICLE_1), 1000, 0.3);
					GameLoop::getInstance().addParticle(p);
					p->movement.y *= (velocity.mag() * 5);
					p->movement.x = 0;
				}
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STRAFE), 1);
			}

		} else {
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
			
		}
}


void Kirby::keyPressEvent(QKeyEvent* e, bool isPressed) {
	

	/* D right
	   S left
	   W enter doors

	   Q inhale / Q exhale
	   E inhale enemies --> E (again) Kirby takes enemy power (If enemy has no power kirby spits it out as bullet)
	   Q (state)+space fly

	   X use special Power
	   Z drop special power

	*/
	// Controls
	if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
		buttons[Kirby::DOWN] = isPressed;
	if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
		buttons[Kirby::RIGHT] = isPressed;
	if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
		buttons[Kirby::LEFT] = isPressed;
	if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
		buttons[Kirby::UP] = isPressed;

	if (e->key() == Qt::Key_Space) {
		buttons[Kirby::SPACE] = isPressed;
		if (!isPressed)
			jumpCooldown = 0;
	}
	if (e->key() == Qt::Key_Q) {
		buttons[Kirby::INHALE_EXHALE] = isPressed;
	}
	if (e->key() == Qt::Key_E) {
		buttons[Kirby::INHALE_ENEMIES] = isPressed;
	}
	if (e->key() == Qt::Key_X) {
		buttons[Kirby::USE_SPECIALPWR] = isPressed;
	}
	if (e->key() == Qt::Key_Z) {
		buttons[Kirby::DROP_SPECIALPWR] = isPressed;
	}
	//enter doors
	if (e->key() == Qt::Key_G && isPressed) {
		buttons[Kirby::ENTERDOOR] = isPressed;

		RigidBody* rb = GameLoop::getInstance().getInside(this);
		//GameObject* obj = getCollidingObject(objects::DOOR); DEPRECATED
		if (rb!=0)
			if(rb->getObjectId() == objects::DOOR)
			(dynamic_cast<Door*>(rb))->launchAction();
			
	}

}