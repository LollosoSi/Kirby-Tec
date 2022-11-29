#pragma once

#include <QGraphicsScene>
#include <QPixmap>

class RenderableObject {

protected:
	uint8_t ZValue = 0;

public:
	RenderableObject* setZValue(uint8_t value) { this->ZValue = value; return this; }
	uint8_t getZValue() const { return ZValue; }

	virtual ~RenderableObject() {}
	virtual void render(QGraphicsScene& scene, bool shouldClear = false) = 0;
	virtual QPixmap getTexture() = 0;

};