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
	float savedtimescale = 1;

	Animatable* current_anim = 0;
	unsigned int cur = 0;
	float time = 0;

	int repeat = 1, repetitions = 0;
	float timescale = 1;

public:
	void tick(double delta);
	void setAnimatable(Animatable* anim, int repeat = 0, float timescale = 1) { this->timescale = timescale; if (current_anim == anim) { repetitions = 0;  return; } repetitions = 0; this->repeat = repeat; current_anim = anim; cur = 0; }
	QPixmap getCurrentPixmap(bool mirror = 0) { return mirror ? current_anim->pixmaps[cur].transformed(QTransform().scale(-1, 1)) : current_anim->pixmaps[cur]; }
	void playOneShot(Animatable* anim, int repeat = 0, float timescale = 1) { if (!next_anim) { next_anim = current_anim;  savedtimescale = timescale; } setAnimatable(anim, repeat, timescale); }
	bool isPlayingOneShot() { return next_anim != 0; }
};