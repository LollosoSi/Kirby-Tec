#pragma once

#include <QString>
#include "Kirby.h"

namespace KA
{
	class LevelBuilder;
	enum class LevelType{ OVERWORLD };

	static inline std::string level2str(LevelType l)
	{
		if (l == LevelType::OVERWORLD)
			return "overworld";
		else
			return "";
	}
}

// @TODO: load/save from/to file
class KA::LevelBuilder
{
	public:

		Kirby* load(const QString& level_name, LevelType & level_type);

};


