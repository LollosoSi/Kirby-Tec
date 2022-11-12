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
		UPCOLLIDER = 30
		
	};
	const int TEXTURE_COUNT = 31;

};

using namespace TexManager;

class TextureManager {

public:
	static TextureManager& getInstance() { static TextureManager instance; return instance; }
	~TextureManager();
	static TextureManager* instance();

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

	//levelbackgroundmap
	
	QRect moveBy(QRect rect, int x, int y = 0, int dx = 16, int dy = 16, int border_x = 4, int border_y = 9);
	QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color);
	QPixmap loadTexture(std::string file, QColor mask_color = Qt::magenta); // load texture with transparency using the given color as mask
	

	Animatable* textures[TEXTURE_COUNT];
	


};