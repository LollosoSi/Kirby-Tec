#pragma once
#include "Definitions.h"
#include "Serializable.h"
#include <sstream>

class Cloneable {
public:
	virtual Cloneable* clone() const = 0;

};

class GameObject : public Serializable, public Cloneable {

public:
	GameObject() : GameObject(0, 0) { }
	GameObject(const double x, const double y) { setX(x); setY(y); setObjectId(objects::GAMEOBJECT); }

	GameObject(const GameObject& go) {
		this->setObjectId(go.getObjectId());
		this->setX(go.getX());
		this->setY(go.getY());
	}
	Cloneable* clone() const { return new GameObject(*this); }

	virtual const double getX() const { return x; }
	virtual const double getY() const { return y; }
	virtual void setX(const double x) { this->x = x; }
	virtual void setY(const double y) { this->y = y; }

	virtual void setObjectId(objects::ObjectID obid) { thisObjectId = obid; }
	virtual objects::ObjectID getObjectId() const { return thisObjectId; }


	std::string serialize(const char& divider) const {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << ((unsigned int)getObjectId()) << divider << getX() << divider << getY();

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator start) {
	
		setX(std::atof((* start).c_str()));
		setY(std::atof((*start).c_str()));	
	
		return this;
	};

	
	

protected:
	double x;
	double y;
	objects::ObjectID thisObjectId;


private:

};
