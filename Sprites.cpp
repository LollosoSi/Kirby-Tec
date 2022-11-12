#include "Sprites.h"


using namespace std;

static QRect getStandardQRect(int x, int y) { return QRect(x, y, 16, 16); }

// Constructor. Load all textures in the Animatable array
TextureManager::TextureManager() {
	QColor kirby_file_mask = QColor(84, 110, 140);
	QColor terrain_file_mask = QColor(60, 188, 252);
	QColor terrain_part2_file_mask = QColor(60, 188, 252);
	QColor nocolor = Qt::transparent;

	// Kirby Movements
	QRect kirby_stand = getStandardQRect(6, 24);
	QRect kirby_walk = getStandardQRect(51, 24);
	QRect kirby_roll = getStandardQRect(6, 49);
	QRect kirby_jump = getStandardQRect(6, 49);

	QRect kirby_strafe = QRect(173, 24, 24, 16);


	// Kirby Actions
	QRect kirby_inhale = getStandardQRect(6, 83); // 2 images (4 totale)
	QRect kirby_inhale2 = QRect(46, 75, 16 , 24 ); // bigger
	QRect kirby_inhale3 = QRect(66, 75, 24, 24); // bigger 2
	QRect kirby_exhale = QRect(160,75,24,24); //1
	QRect kirby_exhale2 = QRect(188, 75, 16, 24); 
	QRect kirby_exhale3 = getStandardQRect(208, 83); //2

	QRect kirby_spit_cloud = getStandardQRect(248,83);

	QRect kirby_big_flying = QRect(99,75,24,24) ; // 2 images
	QRect kirby_big_stand = QRect(63,107,24,24);
	QRect kirby_big_walking = QRect(96,107,24,24); // 3 images

	// Kirby Position
	QRect kirby_sloped_25 = QRect(151, 232, 16, 16);
	QRect kirby_sloped_45 = QRect(171, 232, 16, 23);
	QRect kirby_sloped_25_left = QRect(131, 232, 16, 16);
	QRect kirby_sloped_45_left = QRect(111, 232, 16, 23);

	QRect particle_1 = getStandardQRect(6, 140);

	// title screen
	QRect title_screen = QRect(0, 0, 1023, 895);

	//background
	QRect background = QRect(0, 0, 1008, 168);
	//QRect background1 = QRect(1008, 0, 1008, 168);

	//upcollider
	QRect upcollider = QRect(0, 0, 3040, 232);
	//stage 1
	QRect terrain_1 = getStandardQRect(1,1);
	QRect terrain_2 = getStandardQRect(18,1);
	QRect terrain_3 = getStandardQRect(35,1);
	QRect terrain_4 = getStandardQRect(18,18);
	QRect terrain_5 = getStandardQRect(35,18);
	
//stage 2
	QRect terrain2S_1 = getStandardQRect(120,1);
	QRect terrain2S_2 = getStandardQRect(52,1);
	
//stage 3
	QRect terrain3S_1 = getStandardQRect(69,1);
	QRect terrain3S_2 = getStandardQRect(86,1);
	QRect terrain3S_3 = getStandardQRect(103,1);
	
	// Slopped Section
	QRect terrain_sloped_25 = QRect(272, 33, 62, 32);

	QPixmap kirbytex = loadTexture(file_kirby, kirby_file_mask);
	QPixmap terraintex = loadTexture(file_terrain, terrain_file_mask);
	QPixmap terrainpart2tex = loadTexture(file_terrain_part2, terrain_part2_file_mask);
	QPixmap titlescreentex = loadTexture(file_titlescreen, nocolor);
	QPixmap backgroundtex = loadTexture(file_background, nocolor);
	QPixmap upcollidertex = loadTexture(file_upcollider, nocolor);

	// FORMAT: QPixmap array, float array, size
	textures[KIRBY_WALK] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_walk), 
			kirbytex.copy(moveBy(kirby_walk, 1)),
			kirbytex.copy(moveBy(kirby_walk, 2)),
			kirbytex.copy(moveBy(kirby_walk, 3)) },
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
		4
	};

	textures[KIRBY_STAND] = new Animatable{
		new QPixmap[2]{
			kirbytex.copy(kirby_stand), 
			kirbytex.copy(moveBy(kirby_stand, 1)) },
		new float[2] {2.0f, 0.2f},
		2
	};

	textures[KIRBY_ROLL] = new Animatable{
		new QPixmap[5]{kirbytex.copy(kirby_roll), kirbytex.copy(moveBy(kirby_roll, 1)), kirbytex.copy(moveBy(kirby_roll, 2)), kirbytex.copy(moveBy(kirby_roll, 3)), kirbytex.copy(moveBy(kirby_roll, 4)) },
		new float[5] {0.06f, 0.06f, 0.06f, 0.06f, 0.06f},
		5
	};

	textures[KIRBY_STRAFE] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_strafe)},
		new float[1] {0.06f},
		1
	};

	textures[TERRAIN_SLOPED_25] = new Animatable{
		new QPixmap[1]{terrainpart2tex.copy(terrain_sloped_25)},
		new float[1] {0.06f},
		1
	};
	textures[TERRAIN_SLOPED_45] = new Animatable{
		new QPixmap[1]{terrainpart2tex.copy(terrain_sloped_25)},
		new float[1] {0.06f},
		1
	};

	textures[KIRBY_SLOPED_25] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_25)},
		new float[1] {0.06f},
		1
	};

	textures[KIRBY_SLOPED_45] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_45)},
		new float[1] {0.06f},
		1
	};

	textures[KIRBY_SLOPED_25_LEFT] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_25_left)},
		new float[1] {0.06f},
		1
	};

	textures[KIRBY_SLOPED_45_LEFT] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_45_left)},
		new float[1] {0.06f},
		1
	};

	textures[KIRBY_JUMP] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_jump) },
		new float[1] {0.2f},
		1
	};
//kirby actions
	textures[KIRBY_INHALE] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_inhale),
			kirbytex.copy(moveBy(kirby_inhale, 1)),
			kirbytex.copy(moveBy(kirby_inhale2, 2)),
			kirbytex.copy(moveBy(kirby_inhale3, 3)),
		},
		new float[4] {0.2f , 0.2f , 0.2f , 0.2f},
		1
	};

	textures[KIRBY_EXHALE] = new Animatable{
		new QPixmap[4]{
		kirbytex.copy(kirby_inhale),
		kirbytex.copy(moveBy(kirby_inhale2, 1)),
		kirbytex.copy(moveBy(kirby_exhale3, 2)),
		kirbytex.copy(moveBy(kirby_exhale3, 3)),
		},
		new float[4] {0.2f , 0.2f , 0.2f , 0.2f},
		1
	};

	textures[KIRBY_SPIT_CLOUD] = new Animatable{
		new QPixmap[1]{
			kirbytex.copy(kirby_spit_cloud) },
		new float[1] {0.2f},
		1
	};

	textures[KIRBY_BIG_FLYING] = new Animatable{
		new QPixmap[2]{
			kirbytex.copy(kirby_big_flying),
			kirbytex.copy(moveBy(kirby_big_flying, 1)),
	},
		new float[2] {0.2f, 0.2f},
		1
	};

	textures[KIRBY_BIG_STAND] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_big_stand) },
		new float[1] {0.2f},
		1
	};

	textures[KIRBY_BIG_WALKING] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_big_walking),
			kirbytex.copy(moveBy(kirby_big_flying, 1)),
			kirbytex.copy(moveBy(kirby_big_flying, 2)),
			kirbytex.copy(moveBy(kirby_big_flying, 3)),
			
	},
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
		1
	}; 

// stage 1
	textures[TERRAIN] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_1)},
		new float[1] {0},
		1
	};
	textures[MARGINTERRAINL] = new Animatable{
		new QPixmap[2]{terraintex.copy(terrain_2)},
		new float[1] {0},
		1
	};
	textures[MARGINTERRAINR] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_3)},
		new float[1] {0},
		1
	};
	textures[SECONDTERRAINL] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_4)},
		new float[1] {0},
		1
	};
	textures[SECONDTERRAINR] = new Animatable{
	new QPixmap[1]{terraintex.copy(terrain_5)},
	new float[1] {0},
	1
	};

// stage 2
	textures[TERRAIN2] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain2S_1)},
		new float[1] {0},
		1
	};
	textures[TERRAINBLOCK] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain2S_2)},
		new float[1] {0},
		1
	};
// stage 3
	textures[PLATFORMLEFT] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_1)},
		new float[1] {0},
		1
	};
	textures[PLATFORMCENTER] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_2)},
		new float[1] {0},
		1
	};
	textures[PLATFORMRIGHT] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_2)},
		new float[1] {0},
		1
	};

	// title screen
	textures[TITLESCREEN] = new Animatable{
		new QPixmap[1]{titlescreentex.copy(title_screen)},
		new float[1] {0},
		1
	};

	//background
	textures[BACKGROUND] = new Animatable{
		new QPixmap[2]{
			backgroundtex.copy(background),
			backgroundtex.copy(moveBy(background, 1)),
		},
		new float[2] {0.2f, 0.2f},
		2
		};


	//upcollider
	textures[UPCOLLIDER] = new Animatable{
		new QPixmap[1]{upcollidertex.copy(background)},
		new float[1] {0},
		1
	};

	//particle
	textures[PARTICLE_1] = new Animatable{
		new QPixmap[4]{kirbytex.copy(particle_1), kirbytex.copy(moveBy(particle_1, 1)),kirbytex.copy(moveBy(particle_1, 2)),kirbytex.copy(moveBy(particle_1, 3)) },
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
		4
	};

}

// Destructor
TextureManager::~TextureManager() {
	for (Animatable* a : textures) { delete[] a->pixmaps; delete[] a->duration; delete a; }
	//delete [] textures;
}

// Moves selection
QRect TextureManager::moveBy(QRect rect, int x, int y, int dx, int dy, int border_x, int border_y) {
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
};

// Load texture with transparency using the given color as mask
QPixmap TextureManager::loadTexture(std::string file, QColor mask_color)
{
	QPixmap pixmap(file.c_str());
	//pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

/**  Replaces color
* @Deprecated
*/
QPixmap TextureManager::replaceColor(QPixmap pix, QColor old_color, QColor new_color)
{
	QBitmap mask = pix.createMaskFromColor(old_color, Qt::MaskOutColor);
	
	QPainter p(&pix);
	p.setCompositionMode(QPainter::CompositionMode_SourceOver);
	p.setPen(new_color);
	p.drawPixmap(pix.rect(), mask, mask.rect());
	p.end();
	return pix;
}
/*
QPixmap TextureManager::getLevelBackground(const std::string& level)
{

	QPixmap pix = loadTexture(std::string("/design/MapwithHUD.png"), QColor(147, 187, 236));
	return pix;
}
*/