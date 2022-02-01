#pragma once
#include <string>
#include <functional>
#include <optional>
struct Game
{
	Game() = delete;
	static void Start();
	static void Finish();
	static void HandleInput(const std::string& input);
	static size_t RegisterState(
		std::function<void()> starter,
		std::function<void(const std::string&)> inputHandler);
	static void SetCurrentState(std::optional<size_t> state);
	static bool IsRunning();
};