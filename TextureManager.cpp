#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

QRect TextureManager::moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1) {
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
};

// load texture with transparency using the given color as mask
QPixmap TextureManager::loadTexture(const std::string& file, QColor mask_color = Qt::magenta)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}