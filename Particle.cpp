#include "Particle.h"

#include "GameLoop.h"

void Projectile::tick(double delta) {

	accel.y = 9.8;
	accel.y += movement.y;
	accel.x += movement.x;

	if (hit && circa(velocity.y,0,0.1))
		velocity.y = -2;

	lifetime -= delta * 1000;
	float timeindipendent = (startlifetime - lifetime) / startlifetime;

	RigidBody::tick(delta);
	animator->tick(delta);
	//setX(getX() + (movement.x * pow(M_E, timeindipendent) * delta));
	//setY(getY() + (movement.y * delta));

	std::vector<RigidBody*> objs = GameLoop::getInstance().getInside(this, QRectF(getX(), getY(), pixscale, pixscale));
	for (auto* item : objs) {
		if (instanceof<Enemy, RigidBody>(item)) {
			GameLoop::getInstance().removeElement(dynamic_cast<GameObject*>(item));
			GameLoop::getInstance().addScore(Kirby::getScoreFromObject(item));
			GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (rand() % 26)));
		}
	}
}