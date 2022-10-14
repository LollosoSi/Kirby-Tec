#pragma once

#include <QPixmap>

struct Animatable {
	QPixmap* pixmaps = 0;
	unsigned int size = 0;
};

class TextureManager {
public:
	TextureManager();
	~TextureManager();

private:
	QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1);
	
	// load texture with transparency using the given color as mask
	QPixmap loadTexture(const std::string& file, QColor mask_color = Qt::magenta);

protected:
	QRect kirby_stand_1();
	Animatable kirby_stand{ new QPixmap(){loadTexture}, 2 };


};