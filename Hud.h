#pragma once

#include <QWidget>
#include <QTimer>
#include <QPainter>

#include "RigidBody.h"
#include "Definitions.h"


class ClickableObject {

public:
	virtual bool processClick() = 0;

};

class BaseGUI : public RigidBody, public ClickableObject {

public:
	BaseGUI() : RigidBody() {

	}

	virtual bool processClick() {

	}

	virtual void render(GraphicsScene& scene, bool shouldClear) {
	}

};

class HUD : public QWidget
{
	Q_OBJECT
private:
public:
protected slots:
};

class ScoreItem
{
private:
public:
};