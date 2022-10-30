#include "Kirby.h"

#include "GameLoop.h"
#include "Particle.h"

void Kirby::processAcceleration() {

	PB::Vec2Df temp{ 0.0, 9.8 * scale * 16 };

	if (buttons[UP]) {

	}

	if (buttons[RIGHT] ^ buttons[LEFT]) {
		if (buttons[RIGHT]) {
			mirror = false;
			temp.x += 10 * scale * 16;
		}

		if (buttons[LEFT]) {
			mirror = true;
			temp.x -= 10 * scale * 16;
		}
	}
	else if (isGrounded()) {
		temp.x = (-velocity.x * 3);
		
	}

	if (buttons[DOWN]) {

	}

	if (buttons[SPACE] && isGrounded()) {
		buttons[SPACE] = false;
		temp.y -= 600 * scale * 16;
		this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		this->animator.playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL), 0);
	}

	this->accel = temp;

}

void Kirby::processAnimation() {

	if (!animator.isPlayingOneShot())
		if (isGrounded()) {
			if (abs(velocity.x) < 1 * scale * 16)
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
			else
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));

			if (!(buttons[RIGHT] ^ buttons[LEFT]) && (velocity.mag() > 4*scale*16)) {
				if (!(rand() % 4)) {
					Particle *p;
					GameLoop::getInstance().addParticle(new Particle(QPoint(getX() + ((getSizeX() / 2) * ((rand() % 3) + 1)), getY() + getSizeY()), TextureManager::getInstance().getAnimatable(PARTICLE_1), 1000, 0.3));
					p->movement.y *= (velocity.mag()/(5*scale*16));
				}
				this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STRAFE), 1);
			}

		} else {
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		}

}
