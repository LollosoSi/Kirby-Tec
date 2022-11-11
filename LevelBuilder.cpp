#include "LevelBuilder.h"

#include "Sprites.h"

#include "Waddledee.h"
#include "Waddledoo.h"
#include "Brontoburt.h"
#include "Hothead.h"


using namespace KA;

Kirby* LevelBuilder::load(const QString& level_name, LevelType& level_type)
{
	
	if (level_name == "world-1-1")
	{
		level_type = LevelType::OVERWORLD;

		// death by falling
		

		// palette
		

		// background
		

		// terrains


		
		// enemies
		
		// level end
		

		
	}
	else
	{
		std::cerr << "Cannot load level: level " << level_name.toStdString() << " not found\n";
		return 0;
	}
}