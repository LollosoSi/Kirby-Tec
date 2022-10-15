#pragma once

#include <QPixmap>

#include "objects/TickableObject.h"
#include "TextureManager.h"

class Animator : public TickableObject {
	Animatable* current_anim = 0;
	unsigned int cur = 0;
	double time = 0;
	double mintime = 2;

public:
	void tick(double delta);
	void setAnimatable(Animatable* a) { current_anim = a; cur = 0; }
	QPixmap getCurrentPixmap() { return current_anim->pixmaps[cur]; }
};