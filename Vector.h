#pragma once
#include <math.h>
#include "Definitions.h"

class Vector {

public:
	Vector() : Vector(0, 0) {}
	Vector(numero modx, numero mody) { module_x = modx; module_y = mody; }
	void setModulewithAngle(numero modulo, numero ang) { angle = ang; setModules(modulo * cos(ang), module_y = modulo * sin(ang)); }

	void setModuleX(numero modx) { this->module_x = modx; }
	void setModuleY(numero mody) { this->module_y = mody; }
	void setModules(numero modx, numero mody) { setModuleX(modx); setModuleY(mody); }

	numero getModuleY() { return module_y; }
	numero getModuleX() { return module_x; }
	numero getModule() { return sqrt(pow(getModuleX(), 2) + pow(getModuleY(), 2)); }

private:
	numero module_x = 0, module_y = 0;
	numero angle = 0;

};