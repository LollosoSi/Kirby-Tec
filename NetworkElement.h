#pragma once

#include "Definitions.h"

#include <vector>

#include <fstream>
#include <string>
#include <sstream>

class NetworkObject {

private:
	std::string uuid = "";

public:
	std::string getuuid() {
		if (uuid == "")
			uuid = std::string(rand());
		return uuid;
	}
	virtual std::string pack(const char& divider) {
		return getuuid();
	};
	virtual void sync(std::vector<std::string>::iterator& start) = 0;

};
