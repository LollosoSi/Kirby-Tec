#pragma once

#include <QGraphicsScene>
#include <QPixmap>

class RenderableObject {

protected:
	/* ZValue level index
	* 1 Background
	* 2 Blocks
	* 3 Enemies
	* 4 Kirby
	* 5 Particles
	* 6 Game GUI
	* 7 Pause, Titlescreen
	* 8 Over Pause GUI
	* 9
	* 10
	*/
	uint8_t ZValue = 1;

public:
	RenderableObject* setZValue(uint8_t value) { this->ZValue = value; return this; }
	uint8_t getZValue() const { return ZValue; }

	virtual ~RenderableObject() {}
	virtual void render(QGraphicsScene& scene, bool shouldClear = false) = 0;
	virtual QPixmap getTexture() = 0;

};