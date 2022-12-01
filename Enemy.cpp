#include "Enemy.h"

#include "GameLoop.h"

#define currentpos QPointF(getX(), getY())

double kirbyDistance(QPointF pos) {
	return abs(pitagoricDistance(GameLoop::getInstance().getKirbyPos(), pos));

}

void WaddleDee::tick(double delta)
{
	double dist = kirbyDistance(currentpos);
	if (dist <= 2 && dist >= 1.95 && isGrounded())
		jump(-5);
	
	accel.y = 9.8;

	if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) 
		velocity.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
	
	Enemy::tick(delta);
}

void HotHead::tick(double delta)
{	
	accel.y = 9.8;
	
	if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) 
		accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
	
	Enemy::tick(delta);
}

void PoppyBrosJr::tick(double delta)
{
	accel.y = 9.8;

	
	accel.x = maxwalkspeed * (GameLoop::getInstance().getKirbyPos().x() > getX() ? 1 : -1);
	if (abs(GameLoop::getInstance().getKirbyPos().x() - getX()) < 4 && (GameLoop::getInstance().getKirbyPos().y() < getY()) && isGrounded())
		jump(-7);

	if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0)
		accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);

	Enemy::tick(delta);
}


void BrontoBurt::tick(double delta) {

	time += delta;
	accel.x = -1;
	accel.y = Y_accel * (sin(2 * M_PI * 0.6 * time));

	if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
		accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
		//velocity.x = 0;
		//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
	}
	Enemy::tick(delta);
}


void Sparky::tick(double delta) {
	accel.y = 9.8;
	//if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0) {
		//accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
		//velocity.x = 0;
		//std::cout << "Hit: " << lastHitNormals.x << ":" << lastHitNormals.y << "\n";
	//}

	if (!(rand() % 200)) {
		animator->playOneShot(TextureManager::getInstance().getAnimatable(TexManager::SPARKY_JUMP));
		jump(-4);
	}

	Enemy::tick(delta);
}