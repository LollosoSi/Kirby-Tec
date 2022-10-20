#pragma once

#include <string>

class Serializable {

public:
	virtual std::string serialize(const char &divider) = 0;
	virtual void deserialize(const std::string &data) = 0;

};