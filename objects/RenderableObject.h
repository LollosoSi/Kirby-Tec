#pragma once

#include <QGraphicsScene>

class RenderableObject {


public:
	virtual ~RenderableObject() {}
	virtual void render(QGraphicsScene& scene) = 0;

};