#pragma once

#include "GameObject.h"
#include "Kirby.h"
#include "Terrain.h"

static GameObject* getInstanceOf(objects::ObjectID obj) {
	
	switch (obj) {
	
		default:
			return new GameObject();

		case objects::KIRBY:
			return new Kirby();

		case objects::BACKGROUND:
			return new Background();

		case objects::TERRAIN:
			return new Terrain();

		case objects::SLOPED_TERRAIN_45:
			return new TerrainSloped(objects::SLOPED_TERRAIN_45);
		case objects::SLOPED_TERRAIN_25:
			return new TerrainSloped(objects::SLOPED_TERRAIN_25);
		case objects::SLOPED_TERRAIN_205:
			return new TerrainSloped(objects::SLOPED_TERRAIN_205);
		case objects::SLOPED_TERRAIN_225:
			return new TerrainSloped(objects::SLOPED_TERRAIN_225);

	}

}


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

		std::ifstream target;
		target.open(filename.c_str());

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
			objects.push_back(getInstanceOf(static_cast<objects::ObjectID>(std::atoi((*it).c_str())))->deserialize(++it));

		}

		target.close();
		return objects;
	}

};