#pragma once

#include <QKeyEvent>
#include <string>
#include "Vec2D.h"

namespace PB
{
	// direction type and related utility functions
	enum class Direction { RIGHT, LEFT, UP, DOWN, NONE };
	static std::string dir2str(Direction dir)
	{
		if (dir == Direction::RIGHT)
			return "RIGHT";
		else if (dir == Direction::LEFT)
			return "LEFT";
		else if (dir == Direction::UP)
			return "UP";
		else if (dir == Direction::DOWN)
			return "DOWN";
		else
			return "none";
	}
	static Direction inverse(Direction dir)
	{
		if (dir == Direction::RIGHT)
			return Direction::LEFT;
		else if (dir == Direction::LEFT)
			return Direction::RIGHT;
		else if (dir == Direction::UP)
			return Direction::DOWN;
		else if (dir == Direction::DOWN)
			return Direction::UP;
		else
			return Direction::NONE;
	}
	static Direction key2dir(Qt::Key _keydir)
	{
		if (_keydir == Qt::Key_Right)
			return Direction::RIGHT;
		else if (_keydir == Qt::Key_Left)
			return Direction::LEFT;
		else if (_keydir == Qt::Key_Down)
			return Direction::DOWN;
		else if (_keydir == Qt::Key_Up)
			return Direction::UP;
		else
			return Direction::NONE;
	}
	static Direction normal2dir(Vec2Df _normal)
	{
		if (_normal.x == 0 && _normal.y == 1)
			return Direction::DOWN;
		else if (_normal.x == 0 && _normal.y == -1)
			return Direction::UP;
		else if (_normal.x == 1 && _normal.y == 0)
			return Direction::RIGHT;
		else if (_normal.x == -1 && _normal.y == 0)
			return Direction::LEFT;
		else
			return Direction::NONE;
	}
}