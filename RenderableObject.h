#pragma once

#include <QGraphicsScene>
#include <QPixmap>

class RenderableObject {

public:
	virtual ~RenderableObject() {}

	virtual void render(QGraphicsScene& scene) = 0;
	virtual QPixmap getTexture() = 0;

};