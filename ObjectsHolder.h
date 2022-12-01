#pragma once

#include "GameObject.h"
#include "Kirby.h"
#include "Terrain.h"
#include "Door.h"

#include "Enemy.h"

class ObjectsHolder {


public:
	// Relativi al singleton
	static ObjectsHolder& getInstance() { static ObjectsHolder instance; return instance; }
	~ObjectsHolder() {
		for (auto* item : holder)
			delete item;
	}

	GameObject* getObject(objects::ObjectID obj) {
		return dynamic_cast<GameObject*>(holder[obj]->clone());
	}

private:
	GameObject* holder[objects::totalObjects];
	ObjectsHolder(ObjectsHolder& obj) = delete;
	ObjectsHolder() {
		holder[objects::GAMEOBJECT] = new GameObject();
		holder[objects::KIRBY] = new Kirby();
		holder[objects::SPARKY] = new Sparky();
		holder[objects::BRONTOBURT] = new BrontoBurt();
		holder[objects::POPPYBROSJR] = new PoppyBrosJr();
		holder[objects::SLOPED_TERRAIN] = new TerrainSloped();
		holder[objects::BACKGROUND] = new Background();
		holder[objects::TERRAIN] = new Terrain();
		holder[objects::STEPUP] = new Terrain(objects::STEPUP);
		holder[objects::DOOR] = new Door();
		holder[objects::BARRIER] = new Terrain(objects::BARRIER);
		holder[objects::PLATFORM] = new MovablePlatform();
		holder[objects::WADDLEDEE] = new WaddleDee();
		holder[objects::WADDLEDOO] = new WaddleDoo();
		holder[objects::HOTHEAD] = new HotHead();
		holder[objects::WATER] = new Water();
	}

};

static char objectdivider = '\n', intradivider = '_';
class Serializer {
public:
	static bool serializeToFile(std::vector<Serializable*> objects, std::string filename) {
		std::ofstream target;
		target.open(filename.c_str());

		if (!target.good()) {
			// Whoops, something is off! I don't really care, find a better path and try again.
			target.close();
			//throw "Cannot read file!";
			return false;
		}

		for (Serializable* item : objects) {
			if (objects.front() != item)
				target << objectdivider;
			target << item->serialize(intradivider);
		}

		target.close();
		return true;
	}

	static std::vector<Serializable*> deserializeFromFile(std::string filename) {

		std::vector<Serializable*> objects;

		std::ifstream target(filename.c_str());

		if (!target.good()) {
			// Whoops, something is off! I don't really care, find a better path and try again.
			target.close();
			//throw "Cannot read file!";
			return objects;
		}

		std::string buf;
		while (!target.eof()) {

			getline(target, buf);
			std::stringstream ss(buf);
			std::vector<std::string> data;

			while (!ss.eof()) {
				std::string buf2;
				getline(ss, buf2, intradivider);
				data.push_back(buf2);
			}

			std::vector<std::string>::iterator it = data.begin();
			objects.push_back(ObjectsHolder::getInstance().getObject(static_cast<objects::ObjectID>(std::atoi((*it).c_str())))->deserialize(++it));

		}

		target.close();
		return objects;
	}

};