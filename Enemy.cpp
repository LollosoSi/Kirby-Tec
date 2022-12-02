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

	
	accel.x = 3*maxwalkspeed * (GameLoop::getInstance().getKirbyPos().x() > getX() ? 1 : -1);
	if (abs(GameLoop::getInstance().getKirbyPos().x() - getX()) < 4 && (GameLoop::getInstance().getKirbyPos().y() < getY()) && isGrounded())
		jump(-8);

	if (this->hit && lastHitNormals.x != 0 && lastHitNormals.y == 0)
		accel.x = maxwalkspeed * (velocity.x > 0 ? 1 : -1);
	

	if (!(rand() % 120)) {

		QPointF kirbyPos = GameLoop::getInstance().getKirbyPos();
		QPointF startPos = getCollider().center();

		KA::Vec2Df anglebetweenkirbyandpoppy = getLineBetweenVerts(startPos, kirbyPos);

		double ang = (anglebetweenkirbyandpoppy.x);
		while (ang > M_PI / 4.0) {
			ang -= (M_PI / 4.0);
		}

		double finalangle = 0;
		double xVelFinal = 0;
		double yVelFinal = 0;

		for(double d = 0; d < M_PI/4; d+= M_PI/16){
			double test = d; // the angle we want to test for
			double xVel = (startPos.x()>kirbyPos.x() ? -1 : 1) * sqrt((9.8 * abs(startPos.x() - kirbyPos.x())) / (2.0 * (tan(test) - tan(ang))));
			double yVel = tan(test) * abs(xVel) * (startPos.y() > kirbyPos.y() ? -1 : 1);

			if (abs(xVel) < 60 && abs(yVel) < 60) {
			
				if (xVel > xVelFinal || yVel > yVelFinal) {
					
					xVelFinal = xVel;
					yVelFinal = yVel;
					finalangle = d;

				}
			
			}

		}

		if (xVelFinal == 0)
			return;

		std::cout << "Shooting with xVel: " << xVelFinal << " and yVel: " << yVelFinal << "\n";

		objects::ObjectID targets[] = { objects::KIRBY };
		Projectile* p = new Projectile(getCollider().center(),
			KA::Vec2Df{ 0,0 },
			TextureManager::getInstance().getAnimatable(TexManager::POPPYBROSJR), targets, 1,
			1500, 0.35);
		p->velocity = {xVelFinal, yVelFinal};
		GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(p));
	}

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

		objects::ObjectID targets[] = { objects::KIRBY };

		int steps = 25;
		for (int i = 0; i < steps; i++) {
			Projectile* p = new Projectile(getCollider().center(),
				KA::Vec2Df{ 0,0 },
				TextureManager::getInstance().getAnimatable(TexManager::SPARKY_JUMP), targets, 1,
				1500, 0.15);
			p->velocity = {sin(M_PI * (i - (steps/2.0))/steps), -6 * cos(M_PI * (i - (steps / 2.0)) / steps) };
			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(p));
		}

	}

	Enemy::tick(delta);
}