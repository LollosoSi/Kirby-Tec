#pragma once

typedef int numero;

class GameObject {

public:
	GameObject() : GameObject(0, 0){ }
	GameObject(numero x, numero y) { setX(x); setY(y); }
	virtual numero getX() { return x; }
	virtual numero getY() { return y; }
	virtual void setX(numero x) { this->x = x; }
	virtual void setY(numero y) { this->y = y; }

protected:
	numero x;
	numero y;
private:

};
