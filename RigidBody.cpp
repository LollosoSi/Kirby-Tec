#include "RigidBody.h"

void RigidBody::tick(double deltatime){
	
}


/** Find collision, position is relative to passed object */
collision RigidBody::findCollision(RigidBody& rb) {
#define rbx rb.collider.x()
#define rby rb.collider.y()
#define sizeX rb.collider.width()
#define sizeY rb.collider.height()
#define trbx this->collider.x()
#define trby this->collider.y()
#define tsizeX this->collider.width()
#define tsizeY this->collider.height()


	return 0;

#undef sizeX
#undef sizeY
#undef tsizeX
#undef tsizeY
#undef trbx
#undef trby
#undef rbx
#undef rby
}