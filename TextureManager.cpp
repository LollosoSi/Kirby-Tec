#include "TextureManager.h"


using namespace std;

static QRect getStandardQRect(int x, int y) { return QRect(x, y, 16, 16); }

// Constructor. Load all textures in the Animatable array
TextureManager::TextureManager() {
	QColor kirby_file_mask = QColor(84, 110, 140);

	QRect kirby_stand_1 = getStandardQRect(6, 24);
	QRect kirby_walk_1 = getStandardQRect(51, 24);

	QPixmap kirbytex = loadTexture(file_kirby, kirby_file_mask);

	// FORMAT: QPixmap array, float array, size
	textures[KIRBY_WALK] = new Animatable{
		new QPixmap[4]{kirbytex.copy(kirby_walk_1), kirbytex.copy(moveBy(kirby_walk_1, 1)),kirbytex.copy(moveBy(kirby_walk_1, 2)),kirbytex.copy(moveBy(kirby_walk_1, 3)) },
		new float[4] {0.2f, 0.2f, 0.2f, 0.2f},
		4
	};

	textures[KIRBY_STAND] = new Animatable{
		new QPixmap[2]{kirbytex.copy(kirby_stand_1), kirbytex.copy(moveBy(kirby_stand_1, 1)) },
		new float[2] {2.0f, 0.2f},
		2
	};


}

// Destructor
TextureManager::~TextureManager() {
	for (Animatable* a : textures) { delete[] a->pixmaps; delete[] a->duration; }
	delete [] textures;
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
