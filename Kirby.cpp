#include "Kirby.h"

#include "GameLoop.h"
#include "Particle.h"

void Kirby::processAcceleration() {

	PB::Vec2Df temp{ 0.0, 0.0 };

	if (buttons[RIGHT] ^ buttons[LEFT]) {
		if (buttons[RIGHT] && (velocity.x < maxwalkspeed) ) {
			mirror = false;
			temp.x += (12 * scalefactor) * (1 - abs(velocity.x / maxwalkspeed));
		}

		if (buttons[LEFT] && (velocity.x > -maxwalkspeed) ) {
			mirror = true;
			temp.x -= (12 * scalefactor) * (1 - abs(velocity.x / maxwalkspeed));
		}
	} else if (isGrounded()) {

		temp.x = (-velocity.x * 2);

		
	}

	if (buttons[DOWN]) {

	}

	if (currentDegree != NO_SLOPE) {
		PB::Vec2Df rot = temp;
		double rad = toRadians(renderAngles[currentDegree]);
		rot.x = (temp.x * cos(rad)) - (temp.y * sin(rad));
		rot.y = (temp.x * sin(rad)) + (temp.y * cos(rad));
		temp = rot;
	} else {
	
		temp.y += 9.8 * scalefactor;
	
	}

	if ((buttons[UP] || buttons[SPACE]) && isGrounded() && (lastHitNormals.y < 0)) {
		//buttons[SPACE] = false;
		/* This acceleration must be great velocity in the deltatime frame, usually around 0.001 s */
		jumpImpulse.remainingtime += 50;
		this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		this->animator.playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL), 0);
	}

	if (jumpImpulse.remainingtime > 0)
		temp += jumpImpulse.value;

	this->accel = temp;

}

void Kirby::processAnimation() {

	if (!animator.isPlayingOneShot())
		if (isGrounded()) {
			if (abs(velocity.x) < 1 * scalefactor)
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(
					currentDegree == NO_SLOPE ? KIRBY_STAND : mirror ?
					(currentDegree == SLOPED_25) ? KIRBY_SLOPED_25 : 
					currentDegree == SLOPED_45 ? KIRBY_SLOPED_45 :
					(currentDegree == SLOPED_205) ? KIRBY_SLOPED_25_LEFT : KIRBY_SLOPED_45_LEFT :

					(currentDegree == SLOPED_25) ? KIRBY_SLOPED_25_LEFT :
					currentDegree == SLOPED_45 ? KIRBY_SLOPED_45_LEFT :
					(currentDegree == SLOPED_205) ? KIRBY_SLOPED_25 : KIRBY_SLOPED_45
				
				));
				
			else
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK), 0, 1.3-abs(velocity.x / maxwalkspeed));

			if (!(buttons[RIGHT] ^ buttons[LEFT]) && (velocity.mag() > 4*scalefactor)) {
				if (!(rand() % 2)) {
					Particle *p = new Particle(QPoint(getX() + ((getSizeX() / 5) * ((rand() % 5) + 1)), getY() + getSizeY()), TextureManager::getInstance().getAnimatable(PARTICLE_1), 1000, 0.3);
					GameLoop::getInstance().addParticle(p);
					p->movement.y *= (velocity.mag()/(5*scalefactor));
					p->movement.x = 0;
				}
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STRAFE), 1);
			}

		} else {
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		}

}


void Kirby::keyPressEvent(QKeyEvent* e, bool isPressed) {

	// Controls
	if (e->key() == Qt::Key_S || e->key() == Qt::DownArrow)
		buttons[Kirby::DOWN] = isPressed;
	if (e->key() == Qt::Key_D || e->key() == Qt::RightArrow)
		buttons[Kirby::RIGHT] = isPressed;
	if (e->key() == Qt::Key_A || e->key() == Qt::LeftArrow)
		buttons[Kirby::LEFT] = isPressed;
	if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow)
		buttons[Kirby::UP] = isPressed;

	if (e->key() == Qt::Key_Space)
		buttons[Kirby::SPACE] = isPressed;

}