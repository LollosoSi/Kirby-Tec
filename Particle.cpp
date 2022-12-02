#include "Particle.h"

#include "GameLoop.h"

void Projectile::tick(double delta) {

	if (ignoredObject) {
		setPos(ignoredObject->getCollider().center());
	} else {
		accel.y = 9.8;
		accel.y += movement.y;
		accel.x += movement.x;
		RigidBody::tick(delta);
		if (hit && circa(velocity.y, 0, 0.1))
			velocity.y = -2;
	}

	

	lifetime -= delta * 1000;
	float timeindipendent = (startlifetime - lifetime) / startlifetime;

	
	animator->tick(delta);
	//setX(getX() + (movement.x * pow(M_E, timeindipendent) * delta));
	//setY(getY() + (movement.y * delta));

	std::vector<RigidBody*> objs = GameLoop::getInstance().getInside(this, QRectF(getX(), getY(), pixscale, pixscale));
	for (auto* item : objs) {
		if(ignoredObject != dynamic_cast<GameObject*>(item))
		if (isTarget(item->getObjectId())) {
			if (ignoredObject) 
				ignoredObject->velocity *= -0.5;
			
			lifetime = 0;
			if (item->getObjectId() == objects::KIRBY)
				dynamic_cast<Kirby*>(item)->doDamage();
			else {
				GameLoop::getInstance().removeElement(dynamic_cast<GameObject*>(item));
				GameLoop::getInstance().addScore(Kirby::getScoreFromObject(item));
				GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (rand() % 26)));
			}
		}
	}
}