#include "Kirby.h"
#include "Sounds.h"
#include "GameLoop.h"
#include "Particle.h"

#include <QString>
#include <QFont>
#include <QGraphicsTextItem>

#include "Door.h"
#include "CollisionDetection.h"

using namespace KA;

bool Kirby::isThisTheKirbyInstance() { return dynamic_cast<Kirby*>(GameLoop::getInstance().KirbyInstance) == this; }

int Kirby::getScoreFromObject(GameObject* item) {

	int tempscore = 0;
	if (dynamic_cast<WaddleDoo*>(item)) tempscore += 300;
	if (dynamic_cast<WaddleDee*>(item)) tempscore += 400;
	if (dynamic_cast<PoppyBrosJr*>(item)) tempscore += 400;
	if (dynamic_cast<HotHead*>(item)) tempscore += 600;
	if (dynamic_cast<Sparky*>(item)) tempscore += 600;
	if (dynamic_cast<BrontoBurt*>(item)) tempscore += 1200;
	return tempscore;
}


double Kirby::groundDistance() {

	QPointF start = getCollider().center();
	QPointF ray(0, 10);

	KA::RectF testcollider = getColliderRectF();

	KA::Vec2Df testvelocity{ (double)ray.x(), (double)ray.y() };

	std::vector<std::pair<RigidBody*, double>> raycasted = GameLoop::getInstance().rayCast(this, ray);
	KA::Vec2Df cp, cn;
	double ct = 0, min_t = 1;
	//hit = 0;
	// solve the collisions in correct order 
	for (auto obj : raycasted) {
		if ((obj.first->getObjectId()) != objects::BACKGROUND)
			if (DynamicRectVsRect(testcollider, testvelocity, obj.first->getColliderRectF(), cp, cn, ct) && ct < min_t) {
				if (ct >= 0 && ct < 1 && dynamic_cast<Terrain*>(obj.first))
					return ct*ray.y();
					//std::cout << "HIT ID: " << obj.first->getObjectId() << " AT: " << obj.first->getX() << " : " << obj.first->getY() << " Ray started AT: " << start.x() << " : " << start.y() << "\n";
			}
	}
	return 9999;
}

void Kirby::processAcceleration() {

	if (storedObject) {


		if (buttons[Kirby::THROW_ENEMY]) {
			buttons[Kirby::THROW_ENEMY] = false;

			RigidBody* o;

			// NOTE: PoppyBrosJr is removed from targets
			objects::ObjectID targets[] = { objects::SPARKY, objects::WADDLEDEE, objects::WADDLEDOO, objects::HOTHEAD, objects::BRONTOBURT, objects::POPPYBROSJR };


			Projectile* p = new Projectile(getCollider().center(),
				KA::Vec2Df{ 0,0 }, TextureManager::getInstance().getAnimatable(TexManager::KIRBY_ROLL), targets, 5 + (storedObject ? 1 : 0), 1500, 0.38);

			//}
			//else {

			//}

			o = dynamic_cast<RigidBody*>(p);

			o->velocity.x = (5.0 * (storedObject ? 2 : 1) * (mirror ? -1 : 1)) + getVelocity().x;
			o->velocity.y = -3.0 + getVelocity().y;



			RigidBody* oo = dynamic_cast<RigidBody*>(storedObject);
			oo->setPos(QPointF(getX(), getY()));
			oo->accel = { o->velocity.x,-9.8 };
			damageCooldown = 350;
			storedObject = 0;
			oo->velocity.x = o->getVelocity().x; //(5.0 * (storedObject ? 5 : 1) * (mirror ? -1 : 1)) + getVelocity().x;
			oo->velocity.y = o->getVelocity().y - 2; //-3.0 + getVelocity().y;

			oo->hit = false;

			p->setProtectedObject(oo);

			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(oo));




			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(o));

		}

	}

	

	if (getY() > 15 /* && isThisTheKirbyInstance() */) {
	health = 1;
	damage = 1;
	damageCooldown = 0;
		/*std::thread t(
			[]() {
				GameLoop::getInstance().reload(); 
			}
		);
		t.detach();
		return;*/
	} 

	KA::Vec2Df temp{ 0.0, 9.8 };

	if (!buttons[Kirby::INHALE_ENEMIES] && (buttons[RIGHT] ^ buttons[LEFT])) {
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
		if (storedObject)
			jumpsLeft = 0;
		jumpCooldown = jumpCooldownDefault;
		/* This acceleration must be great velocity in the deltatime frame, usually around 0.001 s */
		jumpImpulse.remainingtime += 30;
		Sounds::instance()->playSound("jump2");
		if (!storedObject) {
			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL), 0);
		}
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

void Kirby::tick(double deltatime) {


	processAcceleration();

	if (jumpImpulse.remainingtime != 0 || jumpCooldown > 0) {
		int time = deltatime * 1000.0;
		jumpImpulse.remainingtime -= time;
		if (jumpImpulse.remainingtime < 0)
			jumpImpulse.remainingtime = 0;

		if (jumpCooldown != 0) {
			if (jumpCooldown < time)
				jumpCooldown = 0;
			else
				jumpCooldown -= time;
		}

	}

	if (damageCooldown > 0) {
		damageCooldown -= deltatime * 1000.0;
		if (damageCooldown < 0)
			damageCooldown = 0;
	}

	processAnimation();
	animator->tick(deltatime);
	RigidBody::tick(deltatime);



	if (damage) {
		if (invincible)
			damage = 0;
		else
		if (!damageCooldown && !(buttons[Kirby::INHALE_ENEMIES] && animator->isPlayingOneShot())) {
			
			damageCooldown = damageCooldownDefault;
			damage = 0;
			if(isThisTheKirbyInstance())
				GameLoop::getInstance().setHealth(--health);
			velocity.y += -6;
			velocity.x *= -1;
			if (health == 0) {
				// die
				health = 6;
				if (isThisTheKirbyInstance()) {
					GameLoop::getInstance().setHealth(health);
					GameLoop::getInstance().setLives(GameLoop::getInstance().getLives() - 1);
				}

				if (GameLoop::getInstance().getLives() >= 0 && isThisTheKirbyInstance()) {

					std::thread tt(
						[]() {
							GameLoop::getInstance().reload();
						}
					);
					tt.detach();

					return;

				} else if(isThisTheKirbyInstance()) {

					GameLoop::getInstance().setLives(3);

					std::thread t([]() {
						GameLoop::getInstance().loadGame("levels/lobby");
						}
					);
					t.detach();
					return;
				}
			}
		}
		else {
			damage = 0;
		}
	}

	if (buttons[KirbyKeys::INHALE_ENEMIES]) {
		/* WORKING RAYCAST
		QPointF start = getCollider().center();
		QPointF ray(0, 1);

		KA::RectF testcollider = getColliderRectF();

		KA::Vec2Df testvelocity{ (double)ray.x(), (double)ray.y() };

		std::vector<std::pair<RigidBody*, double>> raycasted = GameLoop::getInstance().rayCast(this, ray);
		KA::Vec2Df cp, cn;
		double ct = 0, min_t = 1;
		hit = 0;
		// solve the collisions in correct order
		for (auto& obj : raycasted) {
			if (obj.first->getObjectId() != objects::BACKGROUND)
				if (DynamicRectVsRect(testcollider, testvelocity, obj.first->getColliderRectF(), cp, cn, ct) && ct < min_t) {
					if (ct >= 0 && ct < 1 && obj.first->getObjectId()==objects::WADDLEDEE)
						std::cout << "HIT ID: " << obj.first->getObjectId() << " AT: " << obj.first->getX() << " : " << obj.first->getY() << " Ray started AT: " << start.x() << " : " << start.y() << "\n";
				}
		}*/
		if (!storedObject) {
			std::vector<RigidBody*> objs = GameLoop::getInstance().getInside(this, QRectF(getX() - (mirror ? 1.5 : 0), getY(), 1.5, 3));
			
			for (auto* item : objs) {
				if (instanceof<Enemy, RigidBody>(item) && !storedObject) {
					
					if (0.3 > abs(pitagoricDistance(QPointF(getX(), getY()), QPointF(item->getX(), item->getY())))) {
						//std::cout << "should delete << \n";
						storedObject = item;
						GameLoop::getInstance().removeElement(dynamic_cast<GameObject*>(item), false);

							//	waddle dee has none
							// bronto burt has none
							// waddle doo / beam

							if (storedObject->getObjectId() == 16 ) {
								
								GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (3)));
								buttons[Kirby::USE_SPECIALPWR] = false;
							}
							// hot head / fire
							if (storedObject->getObjectId() == 19 ) {
								buttons[Kirby::USE_SPECIALPWR] = false;
							//	storedObject = false;
								GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (6)));
							}
							// Poppy Bros Jr / cutter
							if (storedObject->getObjectId() == 17 ) {
								
								buttons[Kirby::USE_SPECIALPWR] = false;
							//	storedObject = false;
								GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (5)));
							}
							// Sparky / Spark
							if (storedObject->getObjectId() == 18 ) {
								buttons[Kirby::USE_SPECIALPWR] = false;
							//	storedObject = false;
								GameLoop::getInstance().setAbility((TexID)(HUD_POWER + (18)));
							}
					


						GameLoop::getInstance().addScore(Kirby::getScoreFromObject(item));
						animator->interruptOneShot();

					}
					else {
						item->velocity.x += 1 * (getX() > item->getX() ? 1 : -1);
						item->velocity.y += 1 * (getY() > item->getY() ? 1 : -1);
					}
				}
			}
		}
		else {
			buttons[KirbyKeys::INHALE_ENEMIES] = false;
		}

	}

}

void Kirby::processAnimation() {

	if (!animator->isPlayingOneShot()) {
		if (isGrounded()) {
			
			if (abs(velocity.x) < 0.5) {

				double degang = toDegrees(angle);
				//std::cout << "Angle is " << degang << " Mirror: " << mirror << "\n";
				this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(
					!angle || storedObject ? storedObject ? KIRBY_BIG_STAND : KIRBY_STAND :
					circa(abs(degang), 28, 10) ? (((angle > 0 ? !mirror : mirror) ? KIRBY_SLOPED_25 : KIRBY_SLOPED_25_LEFT)) :
					circa(abs(degang), 57, 10) ? (((angle > 0 ? !mirror : mirror) ? KIRBY_SLOPED_45 : KIRBY_SLOPED_45_LEFT)) :
					storedObject ? KIRBY_BIG_STAND : KIRBY_STAND
				));


			}
			else
				this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(storedObject ? KIRBY_BIG_WALKING : KIRBY_WALK), 0, 1.3 - abs(velocity.x / maxwalkspeed));

			if (!(buttons[RIGHT] ^ buttons[LEFT]) && !buttons[Kirby::INHALE_ENEMIES] && (velocity.mag() > 4) && !storedObject) {
				if (!(rand() % 2)) {
					Particle* p = new Particle(QPointF(getX() + ((getSizeX() / 5) * ((rand() % 5) + 1)), getY() + getSizeY()), TextureManager::getInstance().getAnimatable(PARTICLE_1), 600, 0.3);
					GameLoop::getInstance().addElement(p);
					p->velocity.y = -(abs(velocity.mag())/1.2);
					p->movement.x = -velocity.x/20;
				}
				this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STRAFE), 1);
			}

		}
		else {
			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(storedObject ? KIRBY_BIG_FLYING : KIRBY_JUMP));
			if (circa(groundDistance(), 2, 0.1) && velocity.y>0 && !circa(velocity.x,0,5) && !storedObject) {
				this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL),0,1.6f);
			}

		}

	
		if (buttons[Kirby::INHALE_ENEMIES] && !storedObject) {
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_INHALE));
			Sounds::instance()->playSound("inhale");
		}

		if (buttons[Kirby::INHALE_EXHALE] && !storedObject) {
			status = TexID(KIRBY_FLY);
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_INHALE));
			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_BIG_FLYING),1);

			//set gravity flappy bird
			

		}

		if (buttons[Kirby::INHALE_ENEMIES] && storedObject) {
			
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ASSORB));
			setAbility(storedObject->getObjectId());
			storedObject = 0;

		}



	}
}

void Kirby::render(QGraphicsScene& scene, bool shouldClear) {
	RigidBody::render(scene);

	if (isThisTheKirbyInstance()) {
		double h = (3.0 * (Camera::getInstance().screenheight / scalefactor) / 7.0);
		double w = (Camera::getInstance().screenwidth / scalefactor) / 4.0;
		QPointF pos = (QPointF(getX() - w, getY() - h));
		//std::cout << " # " << getY() << " : " << pos.y() << (!((l++) % 10) ? "\n" : "\t");
		//Camera::getInstance().setX(pos.x());
		//Camera::getInstance().setY(pos.y());
		Camera::getInstance().goTo(pos);
	}
	if(sname.length() > 0) {
		if (shouldClear) {
			scene.removeItem(name);
			delete name;
			name = 0;
		}
		else {
			if (!name) {
				QFont qf("Times", 10, QFont::Bold);
				
				name = scene.addText(QString(sname.c_str()), qf);
				name->setZValue(3);
			}
			if (name) {
				name->setPos(Camera::worldToScreen(QPointF(getX(), getY()-0.6)));
			}
		}
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

	if (e->key() == Qt::Key_Space) {
		buttons[Kirby::SPACE] = isPressed;

		if (isGrounded()) {
			Sounds::instance()->playSound("jump");
		}

		if (!isPressed)
			
			jumpCooldown = 0;
	}
	if (e->key() == Qt::Key_W) {
		buttons[Kirby::INHALE_EXHALE] = isPressed;
		
	}
	if (e->key() == Qt::Key_E) {
		buttons[Kirby::INHALE_ENEMIES] = isPressed;
		
	}
	//assorb
	if (e->key() == Qt::Key_X) {
		storedObject = 0;
		buttons[Kirby::USE_SPECIALPWR] = isPressed;
		this->animator->playOneShot(TextureManager::getInstance().getAnimatable(status));

	} 
	//drop power
	if (e->key() == Qt::Key_Z) {
		buttons[Kirby::DROP_SPECIALPWR] = isPressed;
		status = 0;
		GameLoop::getInstance().setAbility((TexID)(HUD_POWER));
		this->animator->playOneShot(TextureManager::getInstance().getAnimatable(0));

		
	}
	// throw enemy
	if (e->key() == Qt::Key_Q) {
		buttons[Kirby::THROW_ENEMY] = isPressed;
		Sounds::instance()->playSound("kirby_spit_enemy");
	} 
	//enter doors
	if (e->key() == Qt::Key_G && isPressed) {
		buttons[Kirby::ENTERDOOR] = isPressed;
		Sounds::instance()->playSound("Enter_door");
		std::vector <RigidBody*> inside = GameLoop::getInstance().getInside(this);
		if (!inside.empty()) {
			RigidBody* rb = inside.front();
			if (rb->getObjectId() == objects::DOOR)
				(dynamic_cast<Door*>(rb))->launchAction();
		}
	}

}