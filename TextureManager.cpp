#include "TextureManager.h"


using namespace std;

TextureManager::TextureManager() {
	QColor kirby_file_mask = QColor(84, 110, 140);

	QRect kirby_stand_1(6, 24, 16, 16);

	QPixmap kirbytex = loadTexture(file_kirby, kirby_file_mask);

	textures[kirby_stand] = new Animatable{
		new QPixmap[2]{kirbytex.copy(kirby_stand_1), kirbytex.copy(moveBy(kirby_stand_1, 1)) }, 2
	};


}

TextureManager::~TextureManager() {
	for (Animatable* a : textures) delete[] a->pixmaps;
	delete [] textures;
}

QRect TextureManager::moveBy(QRect rect, int x, int y, int dx, int dy, int border_x, int border_y) {
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
};

// load texture with transparency using the given color as mask
QPixmap TextureManager::loadTexture(std::string file, QColor mask_color)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

// replace color (useful for palette changes)
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