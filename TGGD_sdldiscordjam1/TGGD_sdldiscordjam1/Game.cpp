#include "Game.h"
#include "Display.h"
struct State
{
	State(std::function<void()> starter,
		std::function<void()> updater,
		std::function<void(const std::string&)> inputHandler)
		: starter(starter)
		, updater(updater)
		, inputHandler(inputHandler)
	{

	}
	std::function<void()> starter;
	std::function<void()> updater;
	std::function<void(const std::string&)> inputHandler;
};

static std::vector<State> states{};

size_t Game::RegisterState(
	std::function<void()> starter,
	std::function<void()> updater,
	std::function<void(const std::string&)> inputHandler)
{
	auto result = states.size();
	states.emplace_back(starter, updater, inputHandler);
	return result;
}

static std::optional<size_t> currentState{};

void Game::SetCurrentState(std::optional<size_t> state)
{
	if (state != currentState)
	{
		currentState = state;
		if (currentState)
		{
			states.at(*currentState).starter();
		}
	}
}


void Game::Start()
{
}

void Game::Finish()
{

}

void Game::Update()
{
}

void Game::HandleInput(const std::string& input)
{
}

