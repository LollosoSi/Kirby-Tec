#pragma once

#include <QRect>
#include <QPixmap>
#include <QBitmap>
#include <iostream>
#include <string>
#include <QPainter>


struct Animatable {
	QPixmap* pixmaps = 0;
	unsigned int size = 0;
};

static enum {
	kirby_stand = 0,
	kirby_walk = 1
};


class TextureManager {

	

public:
	static TextureManager& getInstance() { static TextureManager instance; return instance; }
	~TextureManager();

	Animatable* getAnimatable(unsigned int position = 0) { return textures[position];}

private:
	TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	const std::string file_kirby = "sprites/Kirby.png";
	const std::string file_enemy = "sprites/Enemies.png";
	

	QRect moveBy(QRect rect, int x, int y = 0, int dx = 16, int dy = 16, int border_x = 4, int border_y = 9);
	QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color); // replace color (useful for palette changes)
	QPixmap loadTexture(std::string file, QColor mask_color = Qt::magenta); // load texture with transparency using the given color as mask

	

	Animatable* textures[2];
	


};