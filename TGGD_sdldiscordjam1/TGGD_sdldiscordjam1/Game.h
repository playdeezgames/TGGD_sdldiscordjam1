#pragma once
#include <string>
struct Game
{
	Game() = delete;
	static void Start();
	static void Finish();
	static void Update();
	static void HandleInput(const std::string& input);
};