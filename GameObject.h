#pragma once
#include "Definitions.h"
#include "Serializable.h"
#include <sstream>
#include <QKeyEvent>

namespace objects {
	const enum ObjectID {
		GAMEOBJECT = 0,
		TERRAIN = 1,
		KIRBY = 2,
		SLOPED_TERRAIN = 3,
		freespace1 = 4,
		freespace2 = 5,
		freespace3 = 6,
		CAMERA = 7,
		PARTICLE = 8,
		BACKGROUND = 9,
		STEPUP = 10,
		DOOR = 11,
		BARRIER = 12,
		PLATFORM = 13,
		HUD = 14,
		WADDLEDEE = 15,
		WADDLEDOO = 16,
		POPPYBROSJR = 17,
		SPARKY = 18,
		HOTHEAD = 19,
		BRONTOBURT = 20,
		WATER = 21
	};
	const uint totalObjects = 22;
}

class Cloneable {
public:
	virtual Cloneable* clone() const = 0;
};

class GameObject : public Serializable, public Cloneable {

public:
	GameObject(objects::ObjectID obid = objects::GAMEOBJECT) : GameObject(0, 0, obid) { }
	GameObject(const double x, const double y, objects::ObjectID obid = objects::GAMEOBJECT) { setX(x); setY(y); setObjectId(obid); }

	GameObject(const GameObject& go) {
		this->setObjectId(go.getObjectId());
		this->setX(go.getX());
		this->setY(go.getY());
	}

	virtual GameObject* setObjectId(objects::ObjectID obid) { thisObjectId = obid; return this; }
	virtual objects::ObjectID getObjectId() const { return thisObjectId; }

	virtual const double getX() const { return x; }
	virtual const double getY() const { return y; }
	virtual void setX(const double x) { this->x = x; }
	virtual void setY(const double y) { this->y = y; }

	GameObject* setPos(QPointF pos) {
		setX(pos.x());
		setY(pos.y());
		return this;
	}

	std::string serialize(const char& divider) const {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << ((unsigned int)getObjectId()) << divider << getX() << divider << getY();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) {
		setX(std::atof((*(start++)).c_str()));
		setY(std::atof((*(start++)).c_str()));

		return this;
	};

	bool* getObjectCharacteristics();
	virtual void keyPressEvent(QKeyEvent* e, bool isPressed) {}
	virtual Cloneable* clone() const { return new GameObject(*this); }

protected:
	objects::ObjectID thisObjectId;
	double x;
	double y;
	

};
