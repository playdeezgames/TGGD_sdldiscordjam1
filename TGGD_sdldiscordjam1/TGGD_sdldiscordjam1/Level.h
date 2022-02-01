#pragma once
#include "Direction.h"
struct Level
{
	Level() = delete;
	static void Reset();
	static void Draw();
	static void Move(const Direction& direction);
	static bool CanMove(const Direction& direction);
};
