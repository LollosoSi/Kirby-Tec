#pragma once

#include <QGraphicsScene>
#include <QPixmap>

class RenderableObject {

public:
	virtual ~RenderableObject() {}

	virtual void render(QGraphicsScene& scene, bool shouldClear = false) = 0;
	virtual QPixmap getTexture() = 0;

};