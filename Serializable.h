#pragma once

#include "Definitions.h"

#include <vector>

#include <fstream>
#include <string>
#include <sstream>

#include "ObjectsHolder.h"

class Serializable {

public:
	virtual std::string serialize(const char &divider) const = 0;
	virtual Serializable* deserialize(std::vector<std::string>::iterator start) = 0;

};

static Serializable* getInstanceFromID(objects::ObjectID id) { 
	switch (id) {

	default:
		return 0;
	
		case objects::KIRBY:
			return new Kirby();
		case objects::TERRAIN:
			return new Terrain();
	
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
			throw "Cannot read file!";
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
			throw "Cannot read file!";
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
			objects.push_back(getInstanceFromID(static_cast<objects::ObjectID>(std::atoi((* it).c_str())))->deserialize(++it));

		}

		target.close();
		return objects;
	}

};