#include "Kirby.h"

void Kirby::processAcceleration() {

	PB::Vec2Df temp{ 0.0, 9.8 * scale * 16 };

	if (buttons[UP]) {

	}

	if (buttons[RIGHT] ^ buttons[LEFT]) {
		if (buttons[RIGHT]) {
			temp.x += 10 * scale * 16;
		}

		if (buttons[LEFT]) {
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
	}

	this->accel = temp;

}

void Kirby::processAnimation() {

	if (isGrounded()) {
		if (abs(velocity.x) < 1 * scale * 16)
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));
		else 
			this->animator.setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_WALK));
	}
	
	if (velocity.x != 0) {
		mirror = velocity.x > 0 ? false : velocity.x < 0 ? true : mirror;
	}
	


}
