#pragma once

#include "Definitions.h"

#include "Serializable.h"

#include <vector>

#include <fstream>
#include <string>
#include <sstream>

class NetworkObject : public Serializable {

private:
	std::string uuid = "";

protected:
	bool shouldSync = false;

public:
	const bool needSync() const { return shouldSync; }
	bool isUuid(std::string compare) {
		return compare == getuuid();
	}
	std::string getuuid() {
		if (uuid == "")
			uuid = std::to_string(rand()%90000);
		return uuid;
	}
	virtual std::string pack(const char& divider) {
		shouldSync = false;
		return getuuid() + divider + Serializable::serialize(divider);
	};
	virtual void sync(std::vector<std::string>::iterator& start) {
		shouldSync = false;
		Serializable::deserialize(start);
	};

};
