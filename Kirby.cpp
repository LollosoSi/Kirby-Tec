#include "Kirby.h"

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
		} else {
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
		}

}
