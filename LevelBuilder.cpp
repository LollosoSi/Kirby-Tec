#include "LevelBuilder.h"
#include "Sprites.h"
#include "Gameloop.h"

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
		std::thread tt = std::thread([]() {
			for (int j = 0; j < 1; j++)
				for (int i = 0; i < 9; i++) {
					Terrain* t = new Terrain(QPointF(i, j));
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
				}


			});


		Kirby* k = new Kirby(QPointF(0.0, -5.0));
		GameLoop::getInstance().addKirby(dynamic_cast<GameObject*>(k));
		//KirbyInstance = 0;
		tt.join();

		
		// enemies
		
		// level end
		

		
	}
	else
	{
		std::cerr << "Cannot load level: level " << level_name.toStdString() << " not found\n";
		return 0;
	}
}