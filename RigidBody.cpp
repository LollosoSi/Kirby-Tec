#include "RigidBody.h"

#include "GameLoop.h"
#include "Definitions.h"
#include "CollisionDetection.h"



void RigidBody::render(QGraphicsScene& scene, bool shouldClear) {

	bool visible = Camera::isVisible(getCollider());
	if (!pm && !visible)
		return;


	KA::RectF rf = getColliderRectF();
	
	 QPen qp;
	 qp.setColor(Qt::blue);
	 

	 if (!visible || shouldClear || (!hitboxenabled && hitbox)) {
		 scene.removeItem(pm);
		 delete pm;
		 pm = 0;

		 if (hitbox) {
			 scene.removeItem(hitbox);
			 delete hitbox;
			 hitbox = 0;
		 }

		 //std::cout << "Cleared " << getObjectId() << "\n";
		 return;
	 }else if (!pm) {
		pm = scene.addPixmap(getTexture());
		pm->setZValue(getZValue());
		//if (hitboxenabled)
		//	hitbox = scene.addRect(getCollider(), qp);
	} 
	
	
	
	 if (pm && !shouldClear) {
		 pm->setPixmap(getTexture());
		 pm->setPos(Camera::worldToScreen(QPointF(getX() + animator->getCurrentOffset().x, getY() + animator->getCurrentOffset().y)));
		 //pm->setRotation(renderAngles[currentDegree]);
		 pm->setScale(scale * rigiddrawscale);

		 if (hitboxenabled) {
			 QPointF p = Camera::worldToScreen(QPointF(rf.pos.x, rf.pos.y));
			 if (hitbox) {
				 scene.removeItem(hitbox);
				 delete hitbox;
			 }
			 hitbox = scene.addRect(QRect(p.x(), p.y(), rf.size.x * scalefactor, rf.size.y * scalefactor), qp);
		 }

	}
	
	

}

void RigidBody::tick(double deltatime){
#define tx getX()
#define ty getY()

	auto tempvel = getVelocity();

	velocity.x += accel.x * deltatime;
	velocity.y += accel.y * deltatime;

	double overridex = 0, overridey = 0;

	bool hasHitSlope = false;
	hit = 0;
	std::vector <RigidBody*> inside = GameLoop::getInstance().getInside(this);
	for(auto* item : inside){
		
		RigidBody* rb = item;
		
			//std::cout << "Inside\n";

			if (dynamic_cast<Enemy*>(rb) || dynamic_cast<Kirby*>(rb)) {
				damage = 1;
			}

			if (rb->getObjectId() == objects::WATER) {
				hit = 1;
				velocity.y += -9.8 * pow(5, (abs(rb->getY() - getY()))) * deltatime;
				angle = 0;
			}

			if (rb->getObjectId() == objects::SLOPED_TERRAIN) {

				hasHitSlope = 1;

				QPointF center = getCollider().center();
				KA::Vec2Df line2 = ((TerrainSloped*)rb)->getHitLine();
				double m1 = -1 / line2.x, q1 = center.y() - (center.x() * m1);
				// std::cout << "Angle: " << toDegrees(line2.x) << std::endl;

				QPointF intersection = findIntersection(m1, q1, line2.x, line2.y);

				double dist = pitagoricDistance(center, intersection);
				if (dist < 0.3) {

					

					//std::cout << "Contact time with slope " << ct << "\n";

					hit = true;

					//currentDegree = (obid == objects::SLOPED_TERRAIN_25) ? SLOPED_25 :(obid == objects::SLOPED_TERRAIN_45) ? SLOPED_45 :(obid == objects::SLOPED_TERRAIN_225) ? SLOPED_225 : SLOPED_205;

					// Our angle is actually calculated for the intersection! Corresponds to line2.x
					angle = line2.x;

					//std::cout << "Distance: " << pitagoricDistance(center, intersection) << "\n";


					// Reset y
					//overridey = (getY() - ((0.4-dist)));

					velocity.y = velocity.y - (dist * deltatime);

					// Remove perpendicular component

					KA::Vec2Df rot = velocity;
					double rad = -angle;
					rot.x = (velocity.x * cos(rad)) - (velocity.y * sin(rad));
					rot.y = (rot.x * sin(rad)) + (rot.y * cos(rad));
					if (rot.y > 0)
						rot.y = 0;

					//rot.y -= 2*dist / pow(ct,2);

					KA::Vec2Df rot2 = rot;
					double rad2 = angle;
					rot2.x = (rot.x * cos(rad2)) - (rot.y * sin(rad2));
					rot2.y = (rot.x * sin(rad2)) + (rot.y * cos(rad2));
					velocity = rot2;


				}

			
		}
	}

	if (inside.empty()) {
		angle = 0;
		hit = 0;
	}
	
		//std::cout << "Accx: " <<  accel.x << " velx: " << velocity.x << std::endl;
		std::vector<std::pair<RigidBody*, double>> cs = GameLoop::getInstance().findCollisions(this);
		KA::Vec2Df cp, cn;
		double ct = 0, min_t = 1;
		hit = 0;
		// solve the collisions in correct order 
		for (auto& obj : cs)
			if (DynamicRectVsRect(getColliderRectF(), getVelocity(), obj.first->getColliderRectF(), cp, cn, ct) && ct < min_t)
			{
				objects::ObjectID obid = obj.first->getObjectId();
				if (obid == objects::SLOPED_TERRAIN) {

					//std::cout << "Contact time with slope " << ct << "\n";

					hit = true;

					QPointF center = getCollider().center();
					KA::Vec2Df line2 = ((TerrainSloped*)obj.first)->getHitLine();
					double m1 = -1 / line2.x, q1 = center.y() - (center.x() * m1);
					// std::cout << "Angle: " << toDegrees(line2.x) << std::endl;

					QPointF intersection = findIntersection(m1, q1, line2.x, line2.y);

					double dist = pitagoricDistance(center, intersection);
					if (dist < 0.3) {

						hasHitSlope = 1;

						//currentDegree = (obid == objects::SLOPED_TERRAIN_25) ? SLOPED_25 :(obid == objects::SLOPED_TERRAIN_45) ? SLOPED_45 :(obid == objects::SLOPED_TERRAIN_225) ? SLOPED_225 : SLOPED_205;

						// Our angle is actually calculated for the intersection! Corresponds to line2.x
						angle = line2.x;

						//std::cout << "Distance: " << pitagoricDistance(center, intersection) << "\n";


						// Reset y
						if (dist < 0.05)
							overridey = (getY() - ((0.3 - dist)));




						velocity.y = velocity.y - (dist * deltatime);

						// Remove perpendicular component

						KA::Vec2Df rot = velocity;
						double rad = -angle;
						rot.x = (velocity.x * cos(rad)) - (velocity.y * sin(rad));
						rot.y = (rot.x * sin(rad)) + (rot.y * cos(rad));
						if (rot.y > 0)
							rot.y = 0;

						//rot.y -= 2*dist / pow(ct,2);

						KA::Vec2Df rot2 = rot;
						double rad2 = angle;
						rot2.x = (rot.x * cos(rad2)) - (rot.y * sin(rad2));
						rot2.y = (rot.x * sin(rad2)) + (rot.y * cos(rad2));
						velocity = rot2;


					}
					else {
						angle = 0;

					}
					//break;

				}
				else if ((obid == objects::TERRAIN || obid == objects::BARRIER) && ct >= 0 && ct < 0.05) {
					hit = 1;
					lastHitNormals = cn;
					//currentDegree = NO_SLOPE;
					angle = 0;

					if (cn.x != 0) {
						overridex = (getX() + (getVelocity().x * ct));
						velocity.x = -velocity.x / 7;
					}
					if (cn.y != 0) {
						overridey = (getY() + (getVelocity().y * ct));
						velocity.y = 0;
					}

				}
				else if (obid == objects::PLATFORM && ct >= -0.3 && ct < 0.2) {
					hit = 1;
					lastHitNormals = cn;
					//currentDegree = NO_SLOPE;
					angle = 0;

					
					
					if (cn.x != 0) {
						//overridex = (getX() + (getVelocity().x * ct));
						velocity.x = -velocity.x / 7;
					}
					if (cn.y != 0) {
						overridey = (getY() + (getVelocity().y * ct));
						velocity.y = 0;
						if (cn.y == 1) {
							velocity.y = (obj.first)->getVelocity().y;
							accel.y = 0;
						}
					}

					


				}
				else if (obid == objects::STEPUP && ct >= 0 && ct < 0.05 && cn.y != 1) {
					hit = 1;
					lastHitNormals = cn;
					angle = 0;
					if (cn.y != 0) {
						overridey = (getY() + (getVelocity().y * ct));
						velocity.y = 0;
					}

				}




				//std::cout << "Contact point at: " << cp.x << ":" << cp.y << " Contact time: " << ct << std::endl;



			}
	
	
		
			
			if (!hasHitSlope)
				angle = 0;

	if (angle != 0) {

		//velocity.y = velocity.y - (-9.8 * deltatime);

		KA::Vec2Df rot = tempvel;
		double rad = -angle;
		rot.x = (tempvel.x * cos(rad)) - (tempvel.y * sin(rad));
		rot.y = (rot.x * sin(rad)) + (rot.y * cos(rad));
		if (rot.y > 0)
			rot.y = 0;

		rot.x += accel.x * deltatime;
		rot.y += accel.y * deltatime;

		if(rot.y > 0)
			rot.y = 0;


		KA::Vec2Df rot2 = tempvel;
		double rad2 = angle;
		rot2.x = (rot.x * cos(rad2)) - (rot.y * sin(rad2));
		rot2.y = (rot.x * sin(rad2)) + (rot.y * cos(rad2));
		velocity = rot2;

		//overridex += tx + (velocity.x * deltatime);
		//overridey += ty + (velocity.y * deltatime);
	}

	


	double futurex = !overridex ? tx + (velocity.x * deltatime) : overridex, futurey = !overridey ? ty + (velocity.y * deltatime) : overridey;

	setX(futurex);
	setY(futurey);

#undef tx
#undef ty
}

GameObject* RigidBody::getCollidingObject(objects::ObjectID filter){

	double overridex = 0, overridey = 0;


	//std::cout << "Accx: " <<  accel.x << " velx: " << velocity.x << std::endl;

	std::vector<std::pair<RigidBody*, double>> cs = GameLoop::getInstance().findCollisions(this);

	KA::Vec2Df cp, cn;
	double ct = 0, min_t = 1;
	bool hit = 0;
	// solve the collisions in correct order 
	for (auto& obj : cs)
		if (DynamicRectVsRect(getColliderRectF(), getVelocity(), obj.first->getColliderRectF(), cp, cn, ct) && ct < min_t)
			if (obj.first->getObjectId() == filter && ct >= -0.3 && ct <= 0) 
				return dynamic_cast<GameObject*>(obj.first);

	return 0;
}


/** Find if line mx + q intersects p1 and p2
* NOTE: if m = INT_MAX then line will be y wide at x = q
*/
/*Collision* lineIntersects(double& m, double& q, Point& pmin, Point& pmax, Point& minrange, Point& maxrange) {

	bool xmininrange = pmin.x <= maxrange.x && pmin.x >= minrange.x;

	bool xmaxinrange = pmax.x <= maxrange.x && pmax.x >= minrange.x;

	bool ymininrange = pmin.y <= maxrange.y && pmin.y >= minrange.y;

	bool ymaxinrange = pmax.y <= maxrange.y && pmax.y >= minrange.y;

	Collision c1, c2;

	if (xmininrange) {
		double y = m == INT_MAX ? q : (m * pmin.x + q);
		if (((ymininrange ? pmin.y : minrange.y) <= y) && ((ymaxinrange ? pmax.y : maxrange.y) >= y))
			c1 = Collision{pmin.x, y, COLLISION_UP};
	}

	if (xmaxinrange) {
		double y = m == INT_MAX ? q : (m * pmax.x + q);
		if (((ymininrange ? pmin.y : minrange.y) <= y) && ((ymaxinrange ? pmax.y : maxrange.y) >= y))
			c2 = Collision{ pmax.x, y, COLLISION_UP };
	}
	
	return new Collision[2]{c1,c2};
}*/



//const double M_PI = 3.14159265358979323846;

/** Find collision, position is relative to caller object 
 * @Nullable
*/
/*Collision RigidBody::findCollision(double future_x, double future_y, RigidBody& rb) {
#define rbx rb.collider.x()
#define rby rb.collider.y()
#define sizeX rb.getSizeX()
#define sizeY rb.getSizeY()
#define trbx this->collider.x()
#define trby this->collider.y()
#define tsizeX this->getSizeX()
#define tsizeY this->getSizeY()

	Collision col;

	// Find potential intersection intervals
	double rv0x = rbx, rv0y = rby,
		rv1x = rbx + sizeX, rv1y = rby,
		rv2x = rbx, rv2y = rby + sizeY,
		rv3x = rbx + sizeX, rv3y = rby + sizeY;
	double rxmax = rv0x > rv3x ? rv0x : rv3x;
	double rxmin = rv0x < rv3x ? rv0x : rv3x;
	double rymax = rv0y > rv3y ? rv0y : rv3y;
	double rymin = rv0y < rv3y ? rv0y : rv3y;
	Point p0{ rv0x, rv0y },
		p1{ rv1x, rv1y },
		p2{ rv2x, rv2y },
		p3{ rv3x, rv3y },
		pmin{ rxmin, rymin },
		pmax{ rxmax, rymax };

	double  startxv0 = trbx, startyv0 = trby,
		startxv1 = trbx + tsizeX, startyv1 = trby,
		startxv2 = trbx, startyv2 = trby + tsizeY,
		startxv3 = trbx + tsizeX, startyv3 = trby + tsizeY;
	Point startpoints[]{ Point{startxv0, startyv0}, Point{startxv1, startyv1}, Point{startxv2, startyv2}, Point{startxv3, startyv3} };

	double  endxv0 = future_x, endyv0 = future_y,
		endxv1 = future_x + tsizeX, endyv1 = future_y,
		endxv2 = future_x, endyv2 = future_y + tsizeY,
		endxv3 = future_x + tsizeX, endyv3 = future_y + tsizeY;

	double gravity_center_x = (endxv3 - endxv0) / 2, gravity_center_y = (endyv3 - endyv0) / 2;
	double gravity_center_distance[]{
		pitagoricDistance(abs(gravity_center_x - startxv0), abs(gravity_center_y - startyv0)),
		pitagoricDistance(abs(gravity_center_x - startxv1), abs(gravity_center_y - startyv1)),
		pitagoricDistance(abs(gravity_center_x - startxv2), abs(gravity_center_y - startyv2)),
		pitagoricDistance(abs(gravity_center_x - startxv3), abs(gravity_center_y - startyv3))
	};

	uint8_t closest_index = 0;
	for (int i = 1; i < 4; i++) {
		if (gravity_center_distance[i] < gravity_center_distance[closest_index])
			closest_index = i;
	}

	double xmax = startxv0 > endxv3 ? startxv0 : endxv3;
	double xmin = startxv0 < endxv3 ? startxv0 : endxv3;

	double ymax = startyv0 > endyv3 ? startyv0 : endyv3;
	double ymin = startyv0 < endyv3 ? startyv0 : endyv3;

	Point minbound{ xmin, ymin };
	Point maxbound{ xmax, ymax };


	// Find m. If x1 = x2 m is infinite (y = infinite and placed on x1 in q)
	double m0 = 0, m1 = 0, m2 = 0, m3 = 0;
	double q0 = startxv0, q1 = startxv1, q2 = startxv2, q3 = startxv3;

	if (endxv0 != startxv0) {
		m0 = (endyv0 - startyv0) / (endxv0 - startxv0);
		q0 = startyv0 - (m0 * startxv0);
	}
	else { m0 = INT_MAX; }

	if (endxv1 != startxv1) {
		m1 = (endyv1 - startyv1) / (endxv1 - startxv1);
		q1 = startyv1 - (m1 * startxv1);
	}
	else { m1 = INT_MAX; }

	if (endxv2 != startxv2) {
		m2 = (endyv2 - startyv2) / (endxv2 - startxv2);
		q2 = startyv2 - (m2 * startxv2);
	}
	else { m2 = INT_MAX; }

	if (endxv3 != startxv3) {
		m3 = (endyv3 - startyv3) / (endxv3 - startxv3);
		q3 = startyv3 - (m3 * startxv3);
	}
	else { m3 = INT_MAX; }


	Collision* intersect[]{
		lineIntersects(m0, q0, pmin, pmax, minbound, maxbound),
		lineIntersects(m1, q1, pmin, pmax, minbound, maxbound),
		lineIntersects(m2, q2, pmin, pmax, minbound, maxbound),
		lineIntersects(m3, q3, pmin, pmax, minbound, maxbound)
	};


	// Find closest directional intersection and delete handle
	Point closest_collision{ endxv3, endyv3 };
	double dist = 99999;
#define nts intersect[i][j]
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			if (nts.direction != NO_COLLISION) {
				double distance = pitagoricDistance(abs( nts.x - startpoints[i].x) , abs(nts.y - startpoints[i].y));
				if (distance < dist) {
					dist = distance;
					closest_collision.x = nts.x;
					closest_collision.y = nts.y;
				}
			}
		}
		delete [] intersect[i];
	}
#undef nts

	for (int i = 0; i < 4; i++) {
	
	}

	if (dist == 99999)
		return col;

	double angolo = (m0 != INT_MAX ? atan(m0) : 0) + (closest_index == 0 ? M_PI : closest_index == 1 ? M_PI * 3 / 2 : closest_index == 2 ? M_PI / 2 : 0);

	Collision final{closest_collision.x, closest_collision.y, COLLISION_UP};

	return final;

#undef sizeX
#undef sizeY
#undef tsizeX
#undef tsizeY
#undef trbx
#undef trby
#undef rbx
#undef rby
}*/