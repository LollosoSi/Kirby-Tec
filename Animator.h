#pragma once

#include <QPixmap>

#include "TickableObject.h"

struct Animatable {
	QPixmap* pixmaps = 0;
	float* duration = 0;
	unsigned int size = 0;
};

class Animator : public TickableObject {
	Animatable* next_anim = 0;
	Animatable* current_anim = 0;
	unsigned int cur = 0;
	float time = 0;

public:
	void tick(double delta);
	void setAnimatable(Animatable* anim) { if (current_anim == anim) return; current_anim = anim; cur = 0; }
	QPixmap getCurrentPixmap(bool mirror = 0) { return mirror ? current_anim->pixmaps[cur].transformed(QTransform().scale(-1, 1)) : current_anim->pixmaps[cur]; }
	void playOneShot(Animatable* anim) { if(!next_anim) next_anim = current_anim; setAnimatable(anim); }
};