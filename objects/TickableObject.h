#pragma once


class TickableObject {

public:
	virtual ~TickableObject() {}
	virtual void tick(double deltatime) = 0;

};