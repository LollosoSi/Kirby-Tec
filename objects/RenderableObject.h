#pragma once

#include <QGraphicsScene>

class RenderableObject {

public:
	virtual void render(QGraphicsScene& scene) = 0;
};