#pragma once
struct Level
{
	Level() = delete;
	static void Reset();
	static void Draw();
	static void Move();
	static bool CanMove();
	static void Rotate();
};
