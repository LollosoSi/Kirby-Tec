#pragma once
#include "GameLoop.h"
#include "RigidBody.h"

class Door : public RigidBody {

	std::string level = "";

public:
	Door(const QPointF& coords, std::string level = std::string("levels/lobby"), const QPointF offset = QPointF(0.0, 0.0), const double sizeX = 1, const double sizeY = 1) : RigidBody(coords, offset, sizeX, sizeY) {
		this->level = level;
		setObjectId(objects::DOOR);
	}

	Door() : Door(QPointF(0.0, 0.0)) {}

	void launchAction() {

		if (!GameLoop::getInstance().loadGame(level + std::string(".save"))) {
			GameLoop::getInstance().loadGame(level);
		}

			
		

	}

	std::string serialize(const char& divider) const override {
		std::stringstream out("", std::ios_base::app | std::ios_base::out);
		out << RigidBody::serialize(divider) << divider << level;

		return out.str();
	}

	Serializable* deserialize(std::vector<std::string>::iterator& start) override {
		RigidBody::deserialize(start);
		level = (*(start++));
		return this;
	};

	QPixmap getTexture() override { return TextureManager::getInstance().getAnimatable(TRANSPARENT)->pixmaps[0]; }


};