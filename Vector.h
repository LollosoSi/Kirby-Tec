#pragma once

typedef int numero;
typedef float angolo;

class Vector {

public:
	Vector() : Vector(0, 0) {}
	Vector(numero modx, numero mody) { module_x = modx; module_y = mody; }
	Vector(numero modulo, angolo ang) { angle = ang; module_x = modulo * cos(ang); module_y = modulo * sin(ang); }

private:
	numero module_x = 0, module_y = 0;
	angolo angle = 0;

};