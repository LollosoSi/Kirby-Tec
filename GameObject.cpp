#include "GameObject.h"

#include "Definitions.h"

#include "TickableObject.h"
#include "RenderableObject.h"
#include "Serializable.h"
#include "RigidBody.h"
#include "Kirby.h"

// NOTICE: Pointer must be handled and deleted later
bool* GameObject::getObjectCharacteristics() {

	bool* characteristics = new bool[5]{
		instanceof<TickableObject, GameObject>(this),
		instanceof<RenderableObject, GameObject>(this),
		instanceof<RigidBody, GameObject>(this),
		instanceof<Serializable, GameObject>(this),
		instanceof<Kirby, GameObject>(this)
	};

	if(getObjectId() == objects::PLATFORM){
		std::cout << "Platform: ";
		for (int i = 0; i<5; i++)
			std::cout << " " << characteristics[i];
		std::cout << "\n";
	}

	return characteristics;
}