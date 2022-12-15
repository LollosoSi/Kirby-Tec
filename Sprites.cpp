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

	QRect intronomi = QRect(-5,-5, 1024, 896);
	QRect introvv1 = QRect(0, 0, 1024, 960);
	QRect drawintro = QRect(0, 0, 990, 990);
	QRect commands = QRect(0, 0, 1024, 896);

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
	QPixmap introvegval1 = loadTexture(file_introvegetablevalley1, nocolor);
	QPixmap commandstex = loadTexture(file_commands, nocolor);
	QPixmap introdraw = loadTexture(file_introdraw, nocolor);
		


	
	

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
	/*
	textures[DRAW_INTRO] = new Animatable{
		new QPixmap[22]{
			introdraw.copy(drawintro),
			introdraw.copy(moveBy(drawintro, 1, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 2, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 3, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 4, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 5, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 6, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 7, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 8, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 9, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 10, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 11, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 12, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 13, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 14, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 15, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 16, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 17, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 18, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 19, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 20, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
			introdraw.copy(moveBy(drawintro, 21, 0, drawintro.width() + 1, drawintro.height() + 1, 0, 0)),
		},

		new float[22] {0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f},

	new KA::Vec2Df[22]{KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),
	KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0)},
		 22
	};
	*/

	textures[COMMANDS_HUD] = new Animatable{
		new QPixmap[8]{
			commandstex.copy(commands),
			commandstex.copy(moveBy(commands, 1, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 2, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 3, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 4, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 5, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 6, 0,commands.width() , commands.height() , 0, 0)),
			commandstex.copy(moveBy(commands, 7, 0,commands.width() , commands.height() , 0, 0)),
		},

		new float[8] {0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f},

		new KA::Vec2Df[8]{KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0),KA::Vec2Df(0,0)},
		8
	};

		/*
	textures[VEGETABLE_VALLEY_INTRO1] = new Animatable{
		new QPixmap[240]{
			introvegval1.copy(introvv1),
			introvegval1.copy(moveBy(introvv1, 1, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 2, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 3, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 4, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 5, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 6, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 7, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 8, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 9, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 10, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 11, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 12, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 13, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 14, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 15, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 16, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 17, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 18, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1, 19, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,20, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,21, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,22, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,23, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,24, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,25, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,26, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,27, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,28, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,29, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,30, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,31, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,32, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,33, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,34, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,35, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,36, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,37, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,38, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,39, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,40, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,41, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,42, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,43, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,44, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,45, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,46, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,47, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,48, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,49, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,50, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,51, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,52, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,53, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,54, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,55, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,56, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,57, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,58, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,59, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,60, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,61, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,62, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,63, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,64, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,65, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,66, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,67, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,68, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,69, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,70, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,71, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,72, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,73, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,74, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,75, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,76, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,77, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,78, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,79, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,80, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,81, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,82, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,83, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,84, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,85, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,86, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,87, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,88, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,89, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,90, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,91, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,92, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,93, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,94, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,95, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,96, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,97, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,98, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,99, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,100, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,101, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,102, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,103, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,104, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,105, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,106, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,107, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,108, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,109, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,110, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,111, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,112, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,113, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,114, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,115, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,116, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,117, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,118, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,119, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,120, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,121, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,122, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,123, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,124, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,125, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,126, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,127, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,128, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,129, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,130, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,131, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,132, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,133, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,134, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,135, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,136, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,137, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,138, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,139, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,140, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,141, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,142, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,143, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,144, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,145, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,146, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,147, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,148, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,149, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,150, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,151, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,152, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,153, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,154, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,155, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,156, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,157, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,158, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,159, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,160, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,161, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,162, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,163, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,164, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,165, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,166, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,167, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,168, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,169, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,170, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,171, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,172, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,173, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,174, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,175, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,176, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,177, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,178, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,179, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,180, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,181, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,182, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,183, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,184, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,185, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,186, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,187, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,188, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,189, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,190, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,191, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,192, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,193, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,194, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,195, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,196, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,197, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,198, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,199, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,200, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,201, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,202, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,203, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,204, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,205, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,206, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,207, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,208, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,209, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,210, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,211, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,212, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,213, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,214, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,215, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,216, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,217, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,218, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,219, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,220, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,221, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,222, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,223, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,224, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,225, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,226, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,227, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,228, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,229, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,230, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,231, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,232, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,233, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,234, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,235, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,236, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,237, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,238, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			introvegval1.copy(moveBy(introvv1,239, 0, introvv1.width() + 1, introvv1.height() + 1, 0, 0)),
			
	},
		new float[240] {0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f,
		0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f },
		new KA::Vec2Df[240]{KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0),
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), 
KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0), KA::Vec2Df(0,0),KA::Vec2Df(0,0), KA::Vec2Df(0,0) },
		240
};

*/

	textures[TITLESCREEN_INTRO] = new Animatable{
		new QPixmap[50],
		new float[50] {0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f},
		new KA::Vec2Df[50] { KA::Vec2Df(0,0)},
		50
	};

	for (int i = 0; i < 50; i++)
{
	textures[TITLESCREEN_INTRO]->pixmaps[i] = hudintronomi.copy(moveBy(intronomi, i, 0, intronomi.width(), intronomi.height(), 0, 0));
}

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