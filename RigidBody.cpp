#include "RigidBody.h"

#include "GameLoop.h"
#include "CollisionDetection.h"


void RigidBody::tick(double deltatime){
#define tx getX()
#define ty getY()

	numero futurex = tx + (vx*deltatime), futurey = ty + (vy*deltatime);


	std::vector<std::pair<RigidBody*, double>> cs = GameLoop::getInstance().findCollisions(this);
	
	PB::Vec2Df cp, cn;
	double ct = 0, min_t = INFINITY;
	// solve the collisions in correct order 
	for (auto& obj: cs)
		if (DynamicRectVsRect(getColliderRectF(), getVelocity(), obj.first->getColliderRectF(), cp, cn, ct))
		{
			setX( tx+(100*deltatime) );
			return;
		}

	setX(futurex);
	setY(futurey);

#undef tx
#undef ty
}


void solve_collisions() {

}

/** Find if line mx + q intersects p1 and p2
* NOTE: if m = INT_MAX then line will be y wide at x = q
*/
Collision* lineIntersects(numero &m, numero &q, Point &pmin, Point &pmax, Point &minrange, Point &maxrange) {

	bool xmininrange = pmin.x <= maxrange.x && pmin.x >= minrange.x;

	bool xmaxinrange = pmax.x <= maxrange.x && pmax.x >= minrange.x;

	bool ymininrange = pmin.y <= maxrange.y && pmin.y >= minrange.y;

	bool ymaxinrange = pmax.y <= maxrange.y && pmax.y >= minrange.y;

	Collision c1, c2;

	if (xmininrange) {
		numero y = m == INT_MAX ? q : (m * pmin.x + q);
		if (((ymininrange ? pmin.y : minrange.y) <= y) && ((ymaxinrange ? pmax.y : maxrange.y) >= y))
			c1 = Collision{pmin.x, y, COLLISION_UP};
	}

	if (xmaxinrange) {
		numero y = m == INT_MAX ? q : (m * pmax.x + q);
		if (((ymininrange ? pmin.y : minrange.y) <= y) && ((ymaxinrange ? pmax.y : maxrange.y) >= y))
			c2 = Collision{ pmax.x, y, COLLISION_UP };
	}
	
	return new Collision[2]{c1,c2};
}


numero pitagoricDistance(numero x, numero y){
	return sqrt(pow(x,2)+pow(y,2));
}

//const double M_PI = 3.14159265358979323846;

/** Find collision, position is relative to caller object 
 * @Nullable
*/
Collision RigidBody::findCollision(numero future_x, numero future_y, RigidBody& rb) {
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
	numero rv0x = rbx, rv0y = rby,
		rv1x = rbx + sizeX, rv1y = rby,
		rv2x = rbx, rv2y = rby + sizeY,
		rv3x = rbx + sizeX, rv3y = rby + sizeY;
	numero rxmax = rv0x > rv3x ? rv0x : rv3x;
	numero rxmin = rv0x < rv3x ? rv0x : rv3x;
	numero rymax = rv0y > rv3y ? rv0y : rv3y;
	numero rymin = rv0y < rv3y ? rv0y : rv3y;
	Point p0{ rv0x, rv0y },
		p1{ rv1x, rv1y },
		p2{ rv2x, rv2y },
		p3{ rv3x, rv3y },
		pmin{ rxmin, rymin },
		pmax{ rxmax, rymax };

	numero  startxv0 = trbx, startyv0 = trby,
		startxv1 = trbx + tsizeX, startyv1 = trby,
		startxv2 = trbx, startyv2 = trby + tsizeY,
		startxv3 = trbx + tsizeX, startyv3 = trby + tsizeY;
	Point startpoints[]{ Point{startxv0, startyv0}, Point{startxv1, startyv1}, Point{startxv2, startyv2}, Point{startxv3, startyv3} };

	numero  endxv0 = future_x, endyv0 = future_y,
		endxv1 = future_x + tsizeX, endyv1 = future_y,
		endxv2 = future_x, endyv2 = future_y + tsizeY,
		endxv3 = future_x + tsizeX, endyv3 = future_y + tsizeY;

	numero gravity_center_x = (endxv3 - endxv0) / 2, gravity_center_y = (endyv3 - endyv0) / 2;
	numero gravity_center_distance[]{
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

	numero xmax = startxv0 > endxv3 ? startxv0 : endxv3;
	numero xmin = startxv0 < endxv3 ? startxv0 : endxv3;

	numero ymax = startyv0 > endyv3 ? startyv0 : endyv3;
	numero ymin = startyv0 < endyv3 ? startyv0 : endyv3;

	Point minbound{ xmin, ymin };
	Point maxbound{ xmax, ymax };


	// Find m. If x1 = x2 m is infinite (y = infinite and placed on x1 in q)
	numero m0 = 0, m1 = 0, m2 = 0, m3 = 0;
	numero q0 = startxv0, q1 = startxv1, q2 = startxv2, q3 = startxv3;

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
	numero dist = 99999;
#define nts intersect[i][j]
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			if (nts.direction != NO_COLLISION) {
				numero distance = pitagoricDistance(abs( nts.x - startpoints[i].x) , abs(nts.y - startpoints[i].y));
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

	numero angolo = (m0 != INT_MAX ? atan(m0) : 0) + (closest_index == 0 ? M_PI : closest_index == 1 ? M_PI * 3 / 2 : closest_index == 2 ? M_PI / 2 : 0);

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
}