#include "Sprites.h"

#include "CollisionDetection.h"

using namespace std;

static QRect getStandardQRect(int x, int y) { return QRect(x, y, 16, 16); }

// Constructor. Load all textures in the Animatable array
TextureManager::TextureManager() {
	done = false;

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

	// Kirby enters doors
	QRect kirby_doors = getStandardQRect(103,314);

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

	QRect background1 = QRect(0, 0, 1016, 168);

	QRect background2 = QRect(0, 0, 1016, 168);

	QRect lobby = QRect(0,0,511,367);
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

	QRect barrier = getStandardQRect(0, 0);
	

	// Slopped Section
	QRect terrain_sloped_25 = QRect(272, 33, 62, 32);

	//HUD
	QRect hud_view = QRect(5,245,248,64);
	
	QRect hud_health = QRect(25,211,8,14);
	QRect hud_lives = QRect(92,212,13,12);
	QRect hud_numbers = QRect(234,214,8,8);

	QRect hud_power_normal = QRect(5, 19, 32, 40);

	QRect hud_pause_power = QRect(558, 44, 192, 128);
	QRect hud_pause_backdrop = QRect(3, 230, 192, 128);

	QRect hud_pause_screen = QRect(256, 3, 248, 224);

	//Enemies
	QRect waddledee = getStandardQRect(95,659);
	QRect waddledoo = getStandardQRect(95,59);

	QRect sparky = getStandardQRect(95,79);
	QRect sparky_jump = getStandardQRect(115,79);

	QRect hothead = getStandardQRect(95, 119);
	QRect poppybrosjr = getStandardQRect(95,758);
	QRect brontoburt = getStandardQRect(95,897);

	QRect intronomi = QRect(0,0, 1023, 896);

	QRect transparent = QRect(153, 25, 2, 2);

	QPixmap kirbytex = loadTexture(file_kirby, kirby_file_mask);
	QPixmap enemytex = loadTexture(file_enemy, nocolor);
	QPixmap terraintex = loadTexture(file_terrain, terrain_file_mask);
	QPixmap terrainpart2tex = loadTexture(file_terrain_part2, terrain_part2_file_mask);
	QPixmap titlescreentex = loadTexture(file_titlescreen, nocolor);
	QPixmap backgroundtex = loadTexture(file_background, nocolor);
	QPixmap backgroundtex1 = loadTexture(file_background1, nocolor);
	QPixmap backgroundtex2 = loadTexture(file_background2, nocolor);
	QPixmap lobbytex = loadTexture(file_lobby, nocolor);
	QPixmap upcollidertex = loadTexture(file_upcollider, nocolor);
	QPixmap barrierstex = loadTexture(file_barriers, nocolor);
	QPixmap hudtex = loadTexture(file_HUDcomponents, nocolor);
	QPixmap hudpausetex = loadTexture(file_HUDpause, nocolor);
	QPixmap hudintronomi = loadTexture(file_HUDtitlescreenintro, nocolor);


	
	

	// FORMAT: QPixmap array, float array, size
	textures[KIRBY_WALK] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_walk), 
			kirbytex.copy(moveBy(kirby_walk, 1)),
			kirbytex.copy(moveBy(kirby_walk, 2)),
			kirbytex.copy(moveBy(kirby_walk, 3)) },
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
		new KA::Vec2Df[4]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },
		4
	};

	textures[TRANSPARENT] = new Animatable{
		new QPixmap[1]{ kirbytex.copy(transparent) },
		new float[1] {1.0f},
		new KA::Vec2Df[1]{KA::Vec2Df(0,0)},
		1
	};

	textures[TITLESCREEN_INTRO] = new Animatable{
		new QPixmap[31]{
			hudintronomi.copy(intronomi),
			hudintronomi.copy(moveBy(intronomi, 1, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 2, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 3, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 4, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 5, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 6, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 7, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 8, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 9, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 10, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 11, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 12, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 13, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 14, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 15, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 16, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 17, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 18, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 19, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 20, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 21, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 22, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 23, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 24, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 25, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 26, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 27, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 28, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 29, 0, intronomi.width()+1, intronomi.height()+1, 0, 0)),
			hudintronomi.copy(moveBy(intronomi, 30, 0, intronomi.width()+1, intronomi.height()+1, 0, 0))
	},
		new float[31] {0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,1.5f},
		new KA::Vec2Df[31]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0)},
		31
	};

	textures[KIRBY_STAND] = new Animatable{
		new QPixmap[2]{
			kirbytex.copy(kirby_stand), 
			kirbytex.copy(moveBy(kirby_stand, 1)) },
		new float[2] {2.0f, 0.2f},
		new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0)},
		2
	};

	textures[KIRBY_ROLL] = new Animatable{
		new QPixmap[5]{kirbytex.copy(kirby_roll), kirbytex.copy(moveBy(kirby_roll, 1)), kirbytex.copy(moveBy(kirby_roll, 2)), kirbytex.copy(moveBy(kirby_roll, 3)), kirbytex.copy(moveBy(kirby_roll, 4)) },
		new float[5] {0.06f, 0.06f, 0.06f, 0.06f, 0.06f},
		new KA::Vec2Df[5]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0)},
		5
	};

	textures[KIRBY_STRAFE] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_strafe)},
		new float[1] {0.06f},
		new KA::Vec2Df[1]{KA::Vec2Df(0,0)},
		1
	};

	textures[KIRBY_DOORS] = new Animatable{
		new QPixmap[2]{kirbytex.copy(kirby_doors),kirbytex.copy(moveBy(kirby_doors, 1))},
		new float[2] {0.06f, 0.06f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2
	};

	textures[TERRAIN_SLOPED_25] = new Animatable{
		new QPixmap[1]{terrainpart2tex.copy(terrain_sloped_25)},
		new float[1] {0.06f},
				new KA::Vec2Df[4]{KA::Vec2Df(0,0) },

		1
	};
	textures[TERRAIN_SLOPED_45] = new Animatable{
		new QPixmap[1]{terrainpart2tex.copy(terrain_sloped_25)},
		new float[1] {0.06f},
				new KA::Vec2Df[4]{KA::Vec2Df(0,0) },

		1
	};

	textures[KIRBY_SLOPED_25] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_25)},
		new float[1] {0.06f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	textures[KIRBY_SLOPED_45] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_45)},
		new float[1] {0.06f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	textures[KIRBY_SLOPED_25_LEFT] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_25_left).transformed(QTransform().scale(-1, 1))},
		new float[1] {0.06f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	textures[KIRBY_SLOPED_45_LEFT] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_sloped_45_left).transformed(QTransform().scale(-1, 1))},
		new float[1] {0.06f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	textures[KIRBY_JUMP] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_jump) },
		new float[1] {0.2f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
//kirby actions
	textures[KIRBY_INHALE] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_inhale),
			kirbytex.copy(moveBy(kirby_inhale, 1)),
			kirbytex.copy(kirby_inhale2),
			kirbytex.copy(kirby_inhale3),
		},
		new float[4] {0.2f , 0.4f , 1.0f , 0.1f},
		new KA::Vec2Df[3]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,-0.25) },
		3
	};

	textures[KIRBY_EXHALE] = new Animatable{
		new QPixmap[4]{
		kirbytex.copy(kirby_inhale),
		kirbytex.copy(moveBy(kirby_inhale2, 1)),
		kirbytex.copy(moveBy(kirby_exhale3, 2)),
		kirbytex.copy(moveBy(kirby_exhale3, 3)),
		},
		new float[4] {0.2f , 0.2f , 0.2f , 0.2f},
				new KA::Vec2Df[4]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		4
	};

	textures[KIRBY_SPIT_CLOUD] = new Animatable{
		new QPixmap[1]{
			kirbytex.copy(kirby_spit_cloud) },
		new float[1] {0.2f},
		new KA::Vec2Df[1]{KA::Vec2Df(0,0)},
		1
	};

	textures[KIRBY_BIG_FLYING] = new Animatable{
		new QPixmap[2]{
			kirbytex.copy(kirby_big_flying),
			kirbytex.copy(moveBy(kirby_big_flying, 1, 0, kirby_big_flying.width(), kirby_big_flying.height(), 4, 4))

	},
		new float[2] {0.2f, 0.2f},
		new KA::Vec2Df[2]{KA::Vec2Df(0,-0.35), KA::Vec2Df(0,-0.35)},

		2
	};

	textures[KIRBY_BIG_STAND] = new Animatable{
		new QPixmap[1]{kirbytex.copy(kirby_big_stand) },
		new float[1] {0.2f},
		new KA::Vec2Df[1]{KA::Vec2Df(0,-0.35)},
		1
	};

	textures[KIRBY_BIG_WALKING] = new Animatable{
		new QPixmap[4]{
			kirbytex.copy(kirby_big_walking),
			kirbytex.copy(moveBy(kirby_big_walking, 1, 0, kirby_big_walking.width(), kirby_big_walking.height(), 4, 4)),
			kirbytex.copy(moveBy(kirby_big_walking, 2, 0, kirby_big_walking.width(), kirby_big_walking.height(), 4, 4)),
			kirbytex.copy(moveBy(kirby_big_walking, 1, 0, kirby_big_walking.width(), kirby_big_walking.height(), 4, 4)),
	},
		new float[4] {0.54f, 0.4f, 0.6f, 0.4f},
		new KA::Vec2Df[4]{KA::Vec2Df(0,-0.35), KA::Vec2Df(0,-0.35), KA::Vec2Df(0,-0.35), KA::Vec2Df(0,-0.35)},

		4
	}; 

// stage 1
	textures[TERRAIN] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_1)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[MARGINTERRAINL] = new Animatable{
		new QPixmap[2]{terraintex.copy(terrain_2)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[MARGINTERRAINR] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_3)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[SECONDTERRAINL] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain_4)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[SECONDTERRAINR] = new Animatable{
	new QPixmap[1]{terraintex.copy(terrain_5)},
	new float[1] {0},
			new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

	1
	};

// stage 2
	textures[TERRAIN2] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain2S_1)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[TERRAINBLOCK] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain2S_2)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
// stage 3
	textures[PLATFORMLEFT] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_1)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[PLATFORMCENTER] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_2)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[PLATFORMRIGHT] = new Animatable{
		new QPixmap[1]{terraintex.copy(terrain3S_2)},
		new float[1] {0},		
		new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	// title screen
	textures[TITLESCREEN] = new Animatable{
		new QPixmap[1]{titlescreentex.copy(title_screen)},
		new float[1] {0},
				new KA::Vec2Df[4]{KA::Vec2Df(0,0) },

		1
	};

	//background
	textures[BACKGROUND] = new Animatable{
		new QPixmap[3]{
			backgroundtex.copy(background),
			backgroundtex.copy(moveBy(background,1,0,background.width(),background.height(),0,0)),
			backgroundtex.copy(moveBy(background,2,0,background.width(),background.height(),0,0))
		},
		new float[3] {0.15f, 0.15f, 0.15f},
				new KA::Vec2Df[3]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		3
		};

	//background
	textures[BACKGROUND1] = new Animatable{
		new QPixmap[3]{
			backgroundtex1.copy(background1),
			backgroundtex1.copy(moveBy(background1,1,0,background1.width(),background1.height(),0,0)),
			backgroundtex1.copy(moveBy(background1,2,0,background1.width(),background1.height(),0,0))
		},
		new float[3] {0.12f, 0.14f, 0.18f},
				new KA::Vec2Df[3]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		3
	};

	textures[BACKGROUND2] = new Animatable{
		new QPixmap[3]{
			backgroundtex2.copy(background2),
			backgroundtex2.copy(moveBy(background2,1,0,background2.width(),background2.height(),0,0)),
			backgroundtex2.copy(moveBy(background2,2,0,background2.width(),background2.height(),0,0))
		},
		new float[3] {0.12f, 0.14f, 0.18f},
				new KA::Vec2Df[3]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		3
	};

	textures[LOBBY] = new Animatable{
		new QPixmap[1] {lobbytex.copy(lobby)},
		new float[1] {0.12f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};


	//upcollider
	textures[UPCOLLIDER] = new Animatable{
		new QPixmap[1]{upcollidertex.copy(background)},
		new float[1] {0},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	//particle
	textures[PARTICLE_1] = new Animatable{
		new QPixmap[4]{kirbytex.copy(particle_1), kirbytex.copy(moveBy(particle_1, 1)),kirbytex.copy(moveBy(particle_1, 2)),kirbytex.copy(moveBy(particle_1, 3)) },
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
				new KA::Vec2Df[4]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		4
	};

	textures[BARRIER_1] = new Animatable{
		new QPixmap[1]{barrierstex.copy(moveBy(barrier, 1, 0, 16, 16, 0, 0))},
		new float[1] {0.2f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	textures[BARRIER_2] = new Animatable{
		new QPixmap[1]{barrierstex.copy(moveBy(barrier, 2, 0, 16, 16, 0, 0))},
		new float[1] {0.2f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	// Load power textures
	for (int i = 0; i < (HUD_NUM_9 - HUD_NUM_0) + 1; i++)
		textures[HUD_NUM_0 + i] = new Animatable{
			new QPixmap[1] {hudtex.copy(moveBy(hud_numbers, i, 0, hud_numbers.width(), hud_numbers.height(), 3, 0))},
			new float[1] {0.2f},
					new KA::Vec2Df[1]{KA::Vec2Df(0,0)},

			1
	};

	// Load power textures
	for(int i = 0; i < (HUD_BYEBYE - HUD_POWER) + 1; i++)
		textures[HUD_POWER+i] = new Animatable{
			new QPixmap[1] {hudtex.copy(moveBy(hud_power_normal, i%9, floor(i/9), hud_power_normal.width()+1, hud_power_normal.height()+1, (40-37), (62-59)))},
			new float[1] {0.2f},
					new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

			1
		};

	textures[HUD_PAUSE_POWER] = new Animatable{
		new QPixmap[1] {hudpausetex.copy(hud_pause_power)},
		new float[1] {0.2f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	// Load power pause explain textures
	for (int i = 0; i < (HUD_PAUSE_WHEEL - HUD_PAUSE_BACKDROP) + 1; i++)
		textures[HUD_PAUSE_BACKDROP + i] = new Animatable{
			new QPixmap[1] {hudpausetex.copy(moveBy(hud_pause_backdrop, i % 5, floor(i / 5), hud_pause_backdrop.width(), hud_pause_backdrop.height(), 3, 3))},
			new float[1] {0.2f},
					new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

			1
	};

	textures[HUD_PAUSE_SCREEN] = new Animatable{
		new QPixmap[1] {hudpausetex.copy(hud_pause_screen)},
		new float[1] {0.2f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0)},

		1
	};
	
	textures[HUD_HEALTH] = new Animatable{
		new QPixmap[2] {
			hudtex.copy(hud_health),
			hudtex.copy(moveBy(hud_health,1,0, hud_health.width(), hud_health.height(), 3, 3))
		},
		new float[2] {0.5f, 0.5f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2
	};
	textures[HUD_LIVES] = new Animatable{
		new QPixmap[4] {
			hudtex.copy(hud_lives),
			hudtex.copy(moveBy(hud_lives,1,0, hud_lives.width(), hud_lives.height(), 2)),
			hudtex.copy(moveBy(hud_lives,2,0, hud_lives.width(), hud_lives.height(), 2)),
			hudtex.copy(moveBy(hud_lives,1,0, hud_lives.width(), hud_lives.height(), 2)),
		},
		new float[4] {0.3f, 0.3f, 0.3f, 0.3f},
		new KA::Vec2Df[4]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		4
	};

	//HUD
	textures[HUD_VIEW] = new Animatable{
		new QPixmap[1] {
			hudtex.copy(hud_view)
		},
		new float[1] {1.0f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};

	// Enemies
	textures[WADDLEDEE] = new Animatable{
		new QPixmap[2] {
		enemytex.copy(waddledee),
		enemytex.copy(moveBy(waddledee,1)),
		},
		new float[2] {0.35f,0.35f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2
	};
	textures[WADDLEDOO] = new Animatable{
		new QPixmap[2] {
		enemytex.copy(waddledoo),
		enemytex.copy(moveBy(waddledoo,1)),
		},
		new float[2] {0.35f,0.35f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2
	};
	textures[BRONTOBURT] = new Animatable{
		new QPixmap[2] {
		enemytex.copy(brontoburt),
		enemytex.copy(moveBy(brontoburt,1)),
		},
		new float[2] {0.35f,0.35f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2
	};
	textures[SPARKY] = new Animatable{
		new QPixmap[1] {
		enemytex.copy(sparky),
		},
		new float[1] {0.35f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[SPARKY_JUMP] = new Animatable{
		new QPixmap[2] {
		enemytex.copy(sparky_jump),
		enemytex.copy(moveBy(sparky_jump,1))

		},
		new float[2] {0.35f, 0.35f},
				new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },

		2

	};


	textures[POPPYBROSJR] = new Animatable{
		new QPixmap[1] {
		enemytex.copy(poppybrosjr),
		},
		new float[1] {0.35f},
				new KA::Vec2Df[1]{KA::Vec2Df(0,0) },

		1
	};
	textures[HOTHEAD] = new Animatable{
		new QPixmap[2] {
		enemytex.copy(hothead),
		enemytex.copy(moveBy(hothead,1)),
		},
		new float[2] {0.35f,0.35f},
		new KA::Vec2Df[2]{KA::Vec2Df(0,0), KA::Vec2Df(0,0) },
		2
	};

	done = true;
}

// Destructor
TextureManager::~TextureManager() {
	for (int i = 0; i < TexManager::TEXTURE_COUNT; i++) {
		if (!textures[i]) {
			std::cout << "Element " << i << " is not assigned or loaded\n";
			continue;
		}
		delete [] textures[i]->pixmaps;
		delete [] textures[i]->duration;
		delete textures[i];
	}
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