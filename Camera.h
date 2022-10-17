#pragma once

#include "GameObject.h"
#include "objects/TickableObject.h"
#include <iostream>

/** Questa classe è un Singleto
* Traccia le coordinate di visualizzazione
* Converte da coordinate gioco a schermo
*/
class Camera : public GameObject, public TickableObject {

public:
	// Relativi al singleton
	static Camera& getInstance() { static Camera instance; return instance; }
	~Camera() {}
	
	void goTo(numero x, numero y) { this->gotoX = x; this->gotoY = y; triggerGoto = true; std::cout << "Going to " << gotoX << " " << gotoY << std::endl; }

	static numero convertY(numero input) { return 100-input; }

	static numero convertScreenXPos(numero xin) { return xin - Camera::getInstance().getX(); }
	static numero convertScreenYPos(numero yin) { return Camera::convertY(yin) - Camera::getInstance().getY(); }
	static numero convertYtoWorldPos(numero screenyin) { return Camera::convertY(screenyin) + Camera::getInstance().getY(); }
	static numero convertXtoWorldPos(numero screenxin) { return screenxin + Camera::getInstance().getY(); }

	void tick(double delta);

protected:
	numero gotoX = 0, gotoY = 0;
	bool triggerGoto = false;

private:
	// Relativi al singleton
	Camera(Camera const&) = delete;
	Camera() : Camera(0, 0) {}
	Camera(numero x, numero y) : GameObject(x, y) {}
	void operator=(Camera const&) = delete;
	//


};