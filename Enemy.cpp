#include "Enemy.h"

#include "GameLoop.h"

void WaddleDee::tick(double delta)
{
	double dist = abs(pitagoricDistance(GameLoop::getInstance().getKirbyPos(), QPointF(getX(), getY())));
	if (dist <= 2 && dist >= 1.95) 
		velocity.y = -5;
	
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