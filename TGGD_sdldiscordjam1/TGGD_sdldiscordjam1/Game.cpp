#include "Game.h"
#include "Display.h"
void Game::Start()
{
	Display::SetColor(0, 255, 0);
	Display::WriteText("Hello, world!");
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
