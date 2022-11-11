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
				for (int i = 0; i < 17; i++) {
					Terrain* t = new Terrain(QPointF(i, j));
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));
				}
				
			Terrain* t = new Terrain(QPointF(17, -1 ), objects::TERRAIN, TexID::MARGINTERRAINL);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t));

			Terrain* t1 = new Terrain(QPointF(18, -1), objects::TERRAIN, TexID::MARGINTERRAINR);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t1));

			for (int j = 0; j < 1; j++)
				for (int i = 0; i < 13; i++) {
					Terrain* t2 = new Terrain(QPointF(i+19, j));
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t2));
				}

			Terrain* t3 = new Terrain(QPointF(32, -1), objects::TERRAIN, TexID::MARGINTERRAINL);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t3));

			for (int i = 0; i < 4; i++) {
				Terrain* t2 = new Terrain(QPointF(i + 33, -1));
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t2));
			}

			Terrain* t4 = new Terrain(QPointF(37, -1), objects::TERRAIN, TexID::MARGINTERRAINR);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t4));

			for (int j = 0; j < 1; j++)
				for (int i = 0; i < 4; i++) {
					Terrain* t5 = new Terrain(QPointF(i + 38, j));
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t5));
				}

			Terrain* t6 = new Terrain(QPointF(42, -1), objects::TERRAIN, TexID::MARGINTERRAINL);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t6));

			for (int i = 0; i < 5; i++) {
				Terrain* t7 = new Terrain(QPointF(i + 43, -1));
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t7));
			}

			for (int j = -4; j < -1; j++) {
				Terrain* t8 = new Terrain(QPointF(48, j), objects::TERRAIN, TexID::SECONDTERRAINL);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t8));
			}

			Terrain* t9 = new Terrain(QPointF(48, -5), objects::TERRAIN, TexID::MARGINTERRAINL);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t9));

			Terrain* t10 = new Terrain(QPointF(49, -5), objects::TERRAIN, TexID::MARGINTERRAINR);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t10));

			for (int j = -4; j < -3; j++) {
				Terrain* t11 = new Terrain(QPointF(49, j), objects::TERRAIN, TexID::SECONDTERRAINR);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t11));
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