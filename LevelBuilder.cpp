#include "LevelBuilder.h"
#include "Sprites.h"
#include "Gameloop.h"



void LevelBuilder::load(const QString& level_name, KA::LevelType& level_type)
{
	
	if (level_name == "world-1-1")
	{
		level_type = KA::LevelType::OVERWORLD;

		// death by falling
		

		// palette
		

		// background
		
		// terrains
		//std::thread tt = std::thread([]() {

			//Camera::getInstance().setX(0);
			Camera::getInstance().setY(-8);

			Background* bkgrnd = new Background(QPointF(0, -8), QPointF(0, 0), 400,500, objects::BACKGROUND, TexID::BACKGROUND);
			GameLoop::getInstance().addToRenderable(dynamic_cast<RenderableObject*>(bkgrnd));
			GameLoop::getInstance().addToTickable(dynamic_cast<TickableObject*>(bkgrnd));
			GameLoop::getInstance().addToSerializable(dynamic_cast<Serializable*>(bkgrnd));
			
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

		/*	Terrain* t9 = new Terrain(QPointF(48, -5), objects::TERRAIN, TexID::MARGINTERRAINL);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t9)); */

			Terrain* t10 = new Terrain(QPointF(49, -5), objects::TERRAIN, TexID::MARGINTERRAINR);
			GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t10));

			for (int j = -4; j < -3; j++) {
				Terrain* t11 = new Terrain(QPointF(49, j), objects::TERRAIN, TexID::SECONDTERRAINR);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t11));
			}
			
				Terrain* t12 = new Terrain(QPointF(50, -3), objects::TERRAIN, TexID::MARGINTERRAINR);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t12));

				Terrain* t13 = new Terrain(QPointF(50, -2), objects::TERRAIN, TexID::SECONDTERRAINR);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t13));
			
				for (int i = 0; i < 11; i++) {
					Terrain* t14 = new Terrain(QPointF(i+51 , -1), objects::TERRAIN, TexID::TERRAIN);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t14));
				}
			
				for (int i = 0; i < 18; i++) {
					Terrain* t15 = new Terrain(QPointF(i + 62, 0), objects::TERRAIN, TexID::TERRAIN2);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t15));
				}
				/*Sloped Section not done
				12 blocks
				 HERE
				*/
				for (int i = 0; i < 7; i++) {
					Terrain* t16 = new Terrain(QPointF(i + 92, 0), objects::TERRAIN, TexID::TERRAIN2);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t16));
				}
				for (int i = 0; i < 3; i++) {
					Terrain* t17 = new Terrain(QPointF(i + 93.5, -1), objects::TERRAIN, TexID::TERRAINBLOCK);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t17));
				}
				for (int i = 0; i < 2; i++) {
					Terrain* t18 = new Terrain(QPointF(i + 94.5, -2), objects::TERRAIN, TexID::TERRAINBLOCK);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t18));
				}
				Terrain* t19 = new Terrain(QPointF( 95.5, -3), objects::TERRAIN, TexID::TERRAINBLOCK);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t19));

				/*Sloped Section not done
				4.5 blocks
				 HERE
				*/
				Terrain* t20 = new Terrain(QPointF(104.5, 1), objects::TERRAIN, TexID::TERRAINBLOCK);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t20));
				Terrain* t21 = new Terrain(QPointF(106.5, 1), objects::TERRAIN, TexID::TERRAINBLOCK);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t21));
				Terrain* t22 = new Terrain(QPointF(108.5, 1), objects::TERRAIN, TexID::TERRAINBLOCK);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t22));
				Terrain* t23 = new Terrain(QPointF(110.5, 1), objects::TERRAIN, TexID::TERRAINBLOCK);
				GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t23));
				
				/*Sloped Section not done
				7.5 blocks
				 HERE
				*/
				for (int i = 0; i < 20; i++) {
					Terrain* t18 = new Terrain(QPointF(i + 118, 0), objects::TERRAIN, TexID::TERRAIN2);
					GameLoop::getInstance().addTerrain(dynamic_cast<GameObject*>(t18));
				}
			//});


		Kirby* k = new Kirby(QPointF(0.0, -5.0));
		GameLoop::getInstance().addKirby(dynamic_cast<GameObject*>(k));
		//KirbyInstance = 0;
		//tt.join();

		
		// enemies
		
		// level end
		

		
	}
	else
	{
		std::cerr << "Cannot load level: level " << level_name.toStdString() << " not found\n";
		
	}
}