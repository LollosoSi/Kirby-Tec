#pragma once

#include "GameObject.h"
#include "objects/TickableObject.h"

/** Questa classe è un Singleto
* Traccia le coordinate di visualizzazione
* Converte da coordinate gioco a schermo
*/
class Camera : public GameObject, public TickableObject {

public:
	// Relativi al singleton
	static Camera& getInstance() { static Camera instance; return instance; }
	~Camera() {}
	
	static numero convertY(numero input) { return 100-input; }

	static numero convertScreenXPos(numero xin) { return xin - Camera::getInstance().getX(); }
	static numero convertScreenYPos(numero yin) { return yin - Camera::getInstance().getY(); }

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