#pragma once


class TickableObject {

public:
	virtual void tick(double deltatime) = 0;

};