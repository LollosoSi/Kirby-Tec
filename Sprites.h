#pragma once

#include <QRect>
#include <QPixmap>
#include <QBitmap>
#include <iostream>
#include <string>
#include <QPainter>

#include "Animator.h"

namespace TexManager {

	/** Elements must be caps */
	enum TexID {
		KIRBY_STAND = 0,
		KIRBY_WALK = 1,
		KIRBY_ROLL = 2,
		KIRBY_JUMP = 3,
		KIRBY_STRAFE = 4,

		TERRAIN = 5,
		PARTICLE_1 = 6,

		KIRBY_SLOPED_25 = 7,
		KIRBY_SLOPED_45 = 8,
		KIRBY_SLOPED_25_LEFT = 9,
		KIRBY_SLOPED_45_LEFT = 10,
		TERRAIN_SLOPED_25 = 11,
		TERRAIN_SLOPED_45 = 12,

		// stage 1
		MARGINTERRAINL = 13,
		MARGINTERRAINR = 14,
		SECONDTERRAINL = 15,
		SECONDTERRAINR = 16,
		// stage 2
		TERRAIN2 = 17,
		TERRAINBLOCK = 18,

		// Stage 3
		PLATFORMLEFT = 19,
		PLATFORMCENTER = 20,
		PLATFORMRIGHT = 21,

		// title screen
		TITLESCREEN = 22,

		// KIRBY ACTION
		KIRBY_INHALE = 23,
		KIRBY_EXHALE = 24,
		KIRBY_SPIT_CLOUD = 25,
		KIRBY_BIG_FLYING = 26,
		KIRBY_BIG_STAND = 27,
		KIRBY_BIG_WALKING = 28,

		BACKGROUND = 29,
		UPCOLLIDER = 30,

		TRANSPARENT = 31,

		BACKGROUND1 = 32,
		BACKGROUND2 = 33,

		KIRBY_DOORS = 34,

		LOBBY = 35,
		BARRIER_1 = 36,
		BARRIER_2 = 37,

		// HUD
		HUD_VIEW = 38,
		HUD_HEALTH = 39,
		HUD_LIVES = 40,
		HUD_STAR = 41,
		
		HUD_POWER = 42,
		HUD_BACKDROP = 43,
		HUD_BALL = 44,
		HUD_BEAM = 45,
		HUD_CRASH = 46,
		HUD_CUTTER = 47,
		HUD_FIRE = 48,
		HUD_FIREBALL = 49,
		HUD_FREEZE = 50,

		HUD_HAMMER = 51,
		HUD_HIGHJUMP = 52,
		HUD_ICE = 53,
		HUD_LASER = 54,
		HUD_LIGHT = 55,
		HUD_MIKE = 56,
		HUD_NEEDLE = 57,
		HUD_PARASOL = 58,
		HUD_SLEEP = 59,

		HUD_SPARK = 60,
		HUD_STARROD = 61,
		HUD_STONE = 62,
		HUD_SWORD = 63,
		HUD_THROW = 64,
		HUD_TORNADO = 65,
		HUD_UFO = 66,
		HUD_WHEEL = 67,
		HUD_MIX = 68,

		HUD_NOTHING = 60,
		HUD_HYPER = 61,
		HUD_WORKSTAR = 62,
		HUD_OUCH = 63,
		HUD_MISS = 64,
		HUD_GOAL = 65,
		HUD_CLEAR = 66,
		HUD_BYEBYE = 67,

			HUD_PAUSE_POWER = 68,
			HUD_PAUSE_BACKDROP = 69,
			HUD_PAUSE_BALL = 70,
			HUD_PAUSE_BEAM = 71,
			HUD_PAUSE_CRASH = 72,
			HUD_PAUSE_CUTTER = 73,
			HUD_PAUSE_FIRE = 74,
			HUD_PAUSE_FIREBALL = 75,
			HUD_PAUSE_FREEZE = 76,

			HUD_PAUSE_HAMMER = 77,
			HUD_PAUSE_HIGHJUMP = 78,
			HUD_PAUSE_ICE = 79,
			HUD_PAUSE_LASER = 80,
			HUD_PAUSE_LIGHT = 81,
			HUD_PAUSE_MIKE = 82,
			HUD_PAUSE_NEEDLE = 83,
			HUD_PAUSE_PARASOL = 84,
			HUD_PAUSE_SLEEP = 85,

			HUD_PAUSE_SPARK = 86,
			HUD_PAUSE_STARROD = 87,
			HUD_PAUSE_STONE = 88,
			HUD_PAUSE_SWORD = 89,
			HUD_PAUSE_THROW = 90,
			HUD_PAUSE_TORNADO = 91,
			HUD_PAUSE_UFO = 92,
			HUD_PAUSE_WHEEL = 93,

			HUD_PAUSE_SCREEN = 94,

			HUD_NUM_0 = 95,
			HUD_NUM_1 = 96,
			HUD_NUM_2 = 97,
			HUD_NUM_3 = 98,
			HUD_NUM_4 = 99,
			HUD_NUM_5 = 100,
			HUD_NUM_6 = 101,
			HUD_NUM_7 = 102,
			HUD_NUM_8 = 103,
			HUD_NUM_9 = 104

	};
	const int TEXTURE_COUNT = 105;

};

using namespace TexManager;

class TextureManager {

public:
	static TextureManager& getInstance() { static TextureManager instance; return instance; }
	~TextureManager();

	Animatable* getAnimatable(unsigned int position = 0) { return textures[position];}
	//QPixmap getLevelBackground(const std::string& level);

private:
	TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	const std::string file_kirby = "sprites/Kirby.png";
	const std::string file_enemy = "sprites/Enemies.png";
	const std::string file_terrain = "sprites/SpriteBlocks.png";
	const std::string file_terrain_part2 = "sprites/KirbyTileLevels.png";
	const std::string file_titlescreen = "sprites/titlescreen.png";
	const std::string file_background = "sprites/back.png";
	const std::string file_upcollider = "sprites/Invisible.png";
	const std::string file_background1 = "sprites/back2.png";
	const std::string file_background2 = "sprites/back3.png";
	const std::string file_lobby = "sprites/VegetableValley.png";
	const std::string file_barriers = "sprites/Base.png";
	const std::string file_HUDcomponents = "sprites/HUD.png";
	const std::string file_HUDpause = "sprites/PauseUnicas.png";
	
	
	QRect moveBy(QRect rect, int x, int y = 0, int dx = 16, int dy = 16, int border_x = 4, int border_y = 9);
	QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color);
	QPixmap loadTexture(std::string file, QColor mask_color = Qt::magenta); // load texture with transparency using the given color as mask
	

	Animatable* textures[TEXTURE_COUNT];
	


};