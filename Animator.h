#pragma once

#include <QPixmap>

#include "GameObject.h"
#include "TickableObject.h"

#include <iostream>

struct Animatable {
	QPixmap* pixmaps = 0;
	float* duration = 0;
	KA::Vec2Df* offset = 0;
	unsigned int size = 0;
};

class Animator : public TickableObject, public Cloneable {

protected:
	Animatable* next_anim = 0;
	float savedtimescale = 1;

	Animatable* current_anim = 0;
	unsigned int cur = 0;
	float time = 0;

	int repeat = 1, repetitions = 0;
	float timescale = 1;

public:
	void tick(double delta);
	void setAnimatable(Animatable* anim, int repeat = 0, float timescale = 1) {
		if (!anim) { std::cout << "Animator received nullptr\n"; }
		this->timescale = timescale;
		if (current_anim == anim) { repetitions = 0;  return; }
		repetitions = 0;
		this->repeat = repeat;
		current_anim = anim;
		cur = 0;
	}
	QPixmap getCurrentPixmap(bool mirror = 0) { return /*!current_anim ? QPixmap() :*/ mirror ? current_anim->pixmaps[cur].transformed(QTransform().scale(-1, 1)) : current_anim->pixmaps[cur]; }
	void playOneShot(Animatable* anim, int repeat = 0, float timescale = 1) { if (!next_anim) { next_anim = current_anim;  savedtimescale = timescale; } setAnimatable(anim, repeat, timescale); }
	bool isPlayingOneShot() { return next_anim != 0; }

	KA::Vec2Df getCurrentOffset() { return current_anim->offset[cur]; }

	Animator() {}
	Animator(const Animator& go) {
		*this = go;
	}
	Animator& operator= (const Animator& go) {
		this->repeat = go.repeat;
		this->timescale = go.timescale;
		this->next_anim = go.next_anim;
		this->current_anim = go.current_anim;
		this->cur = go.cur;
		this->time = go.time;
		this->repetitions = go.repetitions;
		this->savedtimescale = go.savedtimescale;
		return *this;
	}
	Cloneable* clone() const { return new Animator(*this); }
};