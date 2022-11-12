#pragma once

#include <QString>
#include "Kirby.h"
#include <string>

namespace KA
{
	//class LevelBuilder;
	enum class LevelType{ OVERWORLD };

	
}

static inline std::string level2str(KA::LevelType l)
{
	if (l == KA::LevelType::OVERWORLD)
		return "overworld";
	else
		return "";
}

// @TODO: load/save from/to file
class LevelBuilder
{
	public:

	void load(const QString& level_name, KA::LevelType & level_type);

};


