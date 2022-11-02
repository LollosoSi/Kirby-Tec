#pragma once

#include "Definitions.h"

#include <vector>

#include <fstream>
#include <string>
#include <sstream>

class Serializable {

public:
	virtual std::string serialize(const char &divider) const = 0;
	virtual Serializable* deserialize(std::vector<std::string>::iterator start) = 0;

};
