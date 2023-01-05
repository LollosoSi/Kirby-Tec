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
	for (std::pair<RigidBody*, double>& obj : raycasted) {
		if(obj.first)
			if (((obj.first)->getObjectId()) != objects::BACKGROUND)
				if (DynamicRectVsRect(testcollider, testvelocity, obj.first->getColliderRectF(), cp, cn, ct) && ct < min_t) {
					if (ct >= 0 && ct < 1 && dynamic_cast<Terrain*>(obj.first))
						return ct*ray.y();
					//std::cout << "HIT ID: " << obj.first->getObjectId() << " AT: " << obj.first->getX() << " : " << obj.first->getY() << " Ray started AT: " << start.x() << " : " << start.y() << "\n";
				}
	}
	return 9999;
}

void Kirby::timeRelated(double deltatime) {

	// Jump impulse & cooldown count
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

	// Damage cooldown count
	if (damageCooldown > 0) {
		damageCooldown -= deltatime * 1000.0;
		if (damageCooldown < 0)
			damageCooldown = 0;
	}

}


void Kirby::collisionRelated() {

	// Action button related
	// Moved to keypress
	
	// Inhaling related
	if (buttons[KirbyKeys::INHALE_ENEMIES] || animator->isPlaying(TextureManager::getInstance().getAnimatable(KIRBY_INHALE))) {
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
		// If no object is caught, try catching
		if (!storedObject) {
			damageCooldown = 100;
			// Find objects in close range
			std::vector<RigidBody*> objs = GameLoop::getInstance().getInside(this, QRectF(getX() - (mirror ? 1.5 : 0), getY(), 1.5, 3));

			// For each close object
			for (auto* item : objs) {

				// Test if object can be inhaled
				if (instanceof<Enemy, RigidBody>(item) && !storedObject) {

					// Test if object is close enough to be eaten
					if (0.3 > abs(pitagoricDistance(QPointF(getX(), getY()), QPointF(item->getX(), item->getY())))) {
						// Eat object.
						// Can be deleted later -> removeElement(..., FALSE)

						// Stop Inhaling: Key, sound and animation
						buttons[Kirby::INHALE_ENEMIES] = false;
						Sounds::instance()->stopSound("inhale");
						animator->interruptOneShot();
						
						// Store object and remove it from the gameloop. Can be deleted later or readded
						storedObject = item;
						GameLoop::getInstance().removeElement(dynamic_cast<GameObject*>(item), false);

						this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_BIG_STAND));

						// Add score based on the object type
						GameLoop::getInstance().addScore(Kirby::getScoreFromObject(item));
						
					} else {
						// Object in range but not close enough, alter velocity
						item->velocity.x += 1 * (getX() > item->getX() ? 1 : -1);
						item->velocity.y += 1 * (getY() > item->getY() ? 1 : -1);
					}
				}
			}
		}
	}

	// If an object is in store
	if (storedObject) {

		// Throw Enemy is pressed (Action key while something is stored)
		if (buttons[Kirby::THROW_ENEMY]) {
			buttons[Kirby::THROW_ENEMY] = false;

			// NOTE: PoppyBrosJr is removed from targets
			objects::ObjectID targets[] = { objects::SPARKY, objects::WADDLEDEE, objects::WADDLEDOO, objects::HOTHEAD, objects::BRONTOBURT, objects::POPPYBROSJR };

			// Attach object to temporary Projectile for damage
			Projectile* p = new Projectile(getCollider().center(), KA::Vec2Df{ 0,0 }, TextureManager::getInstance().getAnimatable(TexManager::KIRBY_ROLL), targets, 5 + (storedObject ? 1 : 0), 1500, 0.38);

			// Set properties
			p->velocity.x = (5.0 * (storedObject ? 2 : 1) * (mirror ? -1 : 1)) + getVelocity().x;
			p->velocity.y = -3.0 + getVelocity().y;


			// Set properties of the object to be attached to projectile
			RigidBody* oo = dynamic_cast<RigidBody*>(storedObject);
			oo->setPos(QPointF(getX(), getY()));
			oo->accel = { p->velocity.x,-9.8 };
			oo->velocity.x = p->getVelocity().x; //(5.0 * (storedObject ? 5 : 1) * (mirror ? -1 : 1)) + getVelocity().x;
			oo->velocity.y = p->getVelocity().y - 2; //-3.0 + getVelocity().y;
			oo->hit = false;

			// Store object
			p->setProtectedObject(oo);

			// Short Kirby immunity from damage when launching
			damageCooldown = 350;
			// Unstore object
			storedObject = 0;

			// Launch both objects into the loop
			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(oo));
			GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(p));

			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STAND));

		}

	}

	// Drop related
	if (buttons[DROP_SPECIALPWR]) {
		buttons[DROP_SPECIALPWR] = false;

		// Set ability
		setAbility(HUD_POWER);

		// TODO: Throw ability star
	}

	// Check if kirby fell under the current level and trigger death
	if (getY() > 15 /* && isThisTheKirbyInstance() */) {
		health = 1;
		damage = 1;
		damageCooldown = 0;
	}

}

void Kirby::onCollision(RigidBody* rb) {
	//objects::ObjectID targets[] = { objects::SPARKY, objects::WADDLEDEE, objects::WADDLEDOO, objects::HOTHEAD, objects::BRONTOBURT, objects::POPPYBROSJR };
	
	Enemy* t = dynamic_cast<Enemy*>(rb);
	if(t && !invincible && !damageCooldown){

		damage = 1;
		
		if (t->getObjectId() == objects::POPPYBROSJR)
			return;

		GameLoop::getInstance().removeElement(dynamic_cast<GameObject*>(rb));

		
	}


}


void Kirby::movementRelated() {
	// Final acceleration
	KA::Vec2Df temp{ 0.0, status == KIRBY_FLY ? 5.0 : 9.8};

	// Jump reset
	if (isGrounded())
		jumpsLeft = 2;

	// Apply jump
	if (status != KIRBY_FLY && buttons[SPACE] && (lastHitNormals.y < 0) && (jumpImpulse.remainingtime == 0) && jumpsLeft > 0 && jumpCooldown == 0) {
		//buttons[SPACE] = false;
		

		jumpsLeft--;
		if (storedObject)
			jumpsLeft = 0;
		jumpCooldown = jumpCooldownDefault;
		/* This acceleration must be great velocity in the deltatime frame, usually around 0.001 s */
		jumpImpulse.remainingtime += 30;

		if (!storedObject) {
			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_JUMP));
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL), 0);
		}
	}else if (status == KIRBY_FLY && buttons[SPACE]) {
		// Different treatment if flying
		temp.y -= 10.0;
	}

	// Apply jump impulse
	if (jumpImpulse.remainingtime > 0) {
		//temp += jumpImpulse.value;
		velocity += jumpImpulse.value * (jumpImpulse.remainingtime / 1000.0);
		jumpImpulse.remainingtime = 0;

		angle = 0;
		//currentDegree = NO_SLOPE;
	}

	// Apply movement
	if (!buttons[Kirby::INHALE_ENEMIES] && (buttons[RIGHT] ^ buttons[LEFT]) && damage == 0 && (velocity.mag() < maxwalkspeed) ) {
		if (buttons[RIGHT] && (velocity.x < maxwalkspeed)) {
			mirror = false;
			temp.x += (maxwalkspeed * 2) * (1 - abs(velocity.x / maxwalkspeed)) * (velocity.x < 0 ? 2 : 1);
		}

		if (buttons[LEFT] && (velocity.x > -maxwalkspeed)) {
			mirror = true;
			temp.x -= (maxwalkspeed * 2) * (1 - abs(velocity.x / maxwalkspeed)) * (velocity.x > 0 ? 2 : 1);
		}
	}
	else if (isGrounded()) {
		// Grind
		if (abs(velocity.x) > 0.3)
			temp.x = ((velocity.x > 0 ? -1 : 1) * 9.8 * 3);
		else if (abs(velocity.x) > 0)
			velocity.x = 0;
	}

	// Check for damage and apply or deny, reload levels
	// NOTE: Should be applied last due to its acceleration resetting nature
	if (damage) {
		damage = 0;
		// Deny if invincible or in cooldown
		if (!invincible && !damageCooldown) {
			damageCooldown = damageCooldownDefault;

			// Apply damage & movement
			health -= 1;
			Sounds::instance()->playSound("kirby_hit");
			velocity.y += -6;
			velocity.x *= -maxwalkspeed / 3;
			//temp.x = 0;
			//temp.y = 0;

			// Check for health
			if (health == 0) {
				// Kirby should die
				// Set and show new health
				health = 6;
				// Remove one life
				GameLoop::getInstance().setLives(GameLoop::getInstance().getLives() - 1);

				// Reset ability
				setAbility(HUD_POWER);

				std::thread resetThread;
				// Decide if redirect to lobby or reload level
				if (GameLoop::getInstance().getLives() < 0) {
					// Reset lives
					GameLoop::getInstance().setLives(4);

					resetThread = std::thread(
						[]() {
							Door d(QPointF(0, 0), "levels/lobby");
							d.savecurrent = false;
							d.launchAction();
						}
					);
				} else {
					// Reset level
					resetThread= std::thread(
						[]() {
							GameLoop::getInstance().reload();
						}
					);
				}
				resetThread.detach();
			}

			setHealth(health);
		}
	}

	this->accel = temp;
}

void Kirby::animationRelated() {

	

	switch (status) {
	
	case KIRBY_FLY:
		if(!animator->isPlayingOneShot())
		this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_BIG_FLYING));

		if (buttons[Kirby::INHALE_EXHALE] && status == KIRBY_FLY) {
			status = KIRBY_STAND;
			buttons[Kirby::INHALE_EXHALE] = false;
		}

		break;

	default:
		// Various actions
		if (buttons[Kirby::INHALE_ENEMIES] && !storedObject && !animator->isPlaying(TextureManager::getInstance().getAnimatable(KIRBY_INHALE))) {
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_INHALE));
			
			buttons[Kirby::INHALE_ENEMIES] = false;
			
		}

		if (buttons[Kirby::INHALE_EXHALE] && !storedObject) {
			status = KIRBY_FLY;
			this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_BIG_FLYING));
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_INHALE));
			buttons[Kirby::INHALE_EXHALE] = false;
			Sounds::instance()->stopSound("inhale");
			
		}


		if (buttons[Kirby::USE_SPECIALPWR] && storedObject) {

			Sounds::instance()->playSound("kirby_takes_enemy");
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ASSORB));
			setAbility(dynamic_cast<Enemy*>(storedObject)->getStoredPower());

			delete storedObject;
			storedObject = 0;

			buttons[Kirby::USE_SPECIALPWR] = false;
			//return;
		}
		else if (buttons[Kirby::USE_SPECIALPWR] && (status != HUD_POWER)) {

			buttons[Kirby::USE_SPECIALPWR] = false;
			objects::ObjectID targets[] = { objects::SPARKY, objects::WADDLEDEE, objects::WADDLEDOO, objects::HOTHEAD, objects::BRONTOBURT, objects::POPPYBROSJR };
			Projectile* pr = 0;
			QPointF pos;
			switch (status) {

			default:
				break;

			case HUD_CUTTER:
			{
				if (animator->isPlayingOneShot())
					return;
				

				pos = getCollider().center();
				pos.setY(pos.y() - 0.4);
				pr = new Projectile(pos,
					KA::Vec2Df{ 0,0 }, TextureManager::getInstance().getAnimatable(TexManager::SWORD), targets, 5, 800, 0.7);

				pr->setCustomGravity(KA::Vec2Df{ 0,0 });
				pr->velocity = KA::Vec2Df{ 12.5* (mirror ? -1 : 1), 0 };

				GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(pr));

			}
				break;

			case HUD_BEAM:

				pos = getCollider().center();
				pos.setY(pos.y() - 0.2);
				pr = new Projectile(pos,
					KA::Vec2Df{ 0,0 }, TextureManager::getInstance().getAnimatable(TexManager::BEAM), targets, 5, 200, 0.7);
				pr->setCustomGravity(KA::Vec2Df{0,0});
				pr->velocity = KA::Vec2Df{ 15.0 * (mirror ? -1 : 1), 0 };

				GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(pr));
				break;

			case HUD_FIRE:
				
				pos = getCollider().center();
				pos.setY(pos.y() - 0.2);
				pr = new Projectile(pos,
					KA::Vec2Df{ 0,0 }, TextureManager::getInstance().getAnimatable(TexManager::FIRE), targets, 5, 400, 0.7);
						
				
				pr->setCustomGravity(KA::Vec2Df{ 0,0 });
				pr->velocity = KA::Vec2Df{ 7.0 * (mirror ? -1 : 1), 0};

				GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(pr));
				break;

			case HUD_SPARK:

				if (!isGrounded() || animator->isPlayingOneShot())
					return;

				double offset = M_PI/8;
				int steps = 4;
				for (int i = 0; i < steps; i++) {
					pr = new Projectile(getCollider().center(),
						KA::Vec2Df{ 0,0 },
						TextureManager::getInstance().getAnimatable(TexManager::SPARK), targets, 5, 200, 0.7);

					pr->setCustomGravity(KA::Vec2Df{ 0, 9.8 });
					//pr->velocity = KA::Vec2Df{ 7.0 * (mirror ? -1 : 1), 0 };

					pr->velocity = { 7*sin(offset + M_PI * (i - (steps / 2.0)) / steps), -15 * cos(offset + M_PI * (i - (steps / 2.0)) / steps) };
					GameLoop::getInstance().addElement(dynamic_cast<GameObject*>(pr));

				}

				break;

				

			}

	


			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(statusToAnimatable(status)), 0);
			return;

		}

		if (isGrounded()) {

			

			// Let play
			if (animator->isPlayingOneShot())
				return;

			// Is kirby almost stopped? Then idle
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

			// Should kirby strafe?
			if (!(buttons[RIGHT] ^ buttons[LEFT]) && !buttons[Kirby::INHALE_ENEMIES] && (velocity.mag() > 4) && !storedObject) {
				if (!(rand() % 2)) {
					Particle* p = new Particle(QPointF(getX() + ((getSizeX() / 5) * ((rand() % 5) + 1)), getY() + getSizeY()), TextureManager::getInstance().getAnimatable(PARTICLE_1), 600, 0.3);
					GameLoop::getInstance().addElement(p);
					p->velocity.y = -(abs(velocity.mag()) / 1.2);
					p->movement.x = -velocity.x / 20;
				}
				this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(KIRBY_STRAFE), 1);
				Sounds::instance()->playSound("kirby_strafe");
			}
			else {
			}
				

		}
		else if(!storedObject && circa(groundDistance(), 1.5, 0.04) && abs(velocity.x)>2 && !animator->isPlayingOneShot()) {
			this->animator->playOneShot(TextureManager::getInstance().getAnimatable(KIRBY_ROLL));
		}

		

		break;
	
	}


}


/** Kirby tick execution flow
* tick
* | > Process time based events
* | -> Process Collision (enemies, doors)
* | --> Process Acceleration
* | ---> Process Animation
* | ----> Animator tick
* | -----> Rigidbody tick
*/
void Kirby::tick(double deltatime) {

	// Do not execute ticking if this is not our player instance.
	// Must be synced via the network instead
	if (!isThisTheKirbyInstance())
		return;

	timeRelated(deltatime);
	collisionRelated();
	movementRelated();
	animationRelated();

	// Look back to stop inhaling if necessary
	if (!animator->isPlaying(TextureManager::getInstance().getAnimatable(KIRBY_INHALE)) && buttons[Kirby::INHALE_ENEMIES]) {
		buttons[Kirby::INHALE_ENEMIES] = false;
		
	}

	animator->tick(deltatime);
	RigidBody::tick(deltatime);

}

void Kirby::setHealth(unsigned int v) {
	if(health != v)
		health = v;
	GameLoop::getInstance().setHealth(health);
}


void Kirby::setAbility(TexID id) {
	GameLoop::getInstance().setAbility(id);
	status = id;
	//this->animator->setAnimatable(TextureManager::getInstance().getAnimatable(statusToAnimatable(status = id)));
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
				name->setZValue(getZValue());
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

	// Puff up
	if (e->key() == Qt::Key_W || e->key() == Qt::UpArrow) {
		buttons[Kirby::UP] = isPressed;
		buttons[Kirby::INHALE_EXHALE] = isPressed;
		Sounds::instance()->playSound("inhale");
	}

	// Jump
	if (e->key() == Qt::Key_Space) {
		buttons[Kirby::SPACE] = isPressed;

		if (!isPressed)
			jumpCooldown = 0;

		if (isGrounded()) {
			Sounds::instance()->playSound("jump");
		}
	}

	// Action button: enter doors OR inhale OR throw
	if (e->key() == Qt::Key_E && isPressed) {
		
		buttons[E] = isPressed;

		if (buttons[E]) {
			buttons[E] = false;

			std::vector <RigidBody*> inside = GameLoop::getInstance().getInside(this);
			if (!inside.empty()) {
				RigidBody* rb = inside.front();
				if (rb->getObjectId() == objects::DOOR) {
				
					Sounds::instance()->playSound("Exit_level");

				
					buttons[Kirby::ENTERDOOR] = 1;

					//setAbility(HUD_POWER);

					Sounds::instance()->playSound("Enter_door");
					
					(dynamic_cast<Door*>(rb))->launchAction(this);

					return;
				}
			}
			else if (storedObject) {
				buttons[Kirby::THROW_ENEMY] = 1;
				Sounds::instance()->playSound("kirby_spit_enemy");
			}
			else if (!animator->isPlayingOneShot()) {
				Sounds::instance()->playSound("inhale");
				buttons[Kirby::INHALE_ENEMIES] = 1;
			}
		}
	}

	// Take ability from enemy
	if (e->key() == Qt::Key_X) {
		buttons[Kirby::USE_SPECIALPWR] = isPressed;

		
		switch (status) {

		default:
			break;

		case HUD_CUTTER:
		{
			Sounds::instance()->playSound("kirby_sword");
			break;
		}
		case HUD_FIRE:
		{
			Sounds::instance()->playSound("kirby_fire");
			break;
		}
		case HUD_BEAM:
		{
			Sounds::instance()->playSound("kirby_beam");
			break;
		}
		case HUD_SPARK:
		{
			Sounds::instance()->playSound("kirby_spark");
			break;
		}

		}
	}
	
	// Drop current ability
	if (e->key() == Qt::Key_Z && isPressed) {
		buttons[Kirby::DROP_SPECIALPWR] = isPressed;


	}
	

}