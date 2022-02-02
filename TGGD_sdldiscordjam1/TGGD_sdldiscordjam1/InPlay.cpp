#include "InPlay.h"
#include <optional>
#include "Game.h"
#include "InputBuffer.h"
#include "Level.h"
#include "Display.h"
#include "Colors.h"
#include "MainMenu.h"
#include <format>
static std::optional<size_t> stateId{};

size_t InPlay::GetStateId()
{
	return stateId.value();
}

static void Refresh()
{
	Level::Draw();
	Display::SetColor(Colors::GRAY);
	Display::WriteLine(std::format("Moves: {}", Level::GetMoveCounter()));
	Display::WriteLine();
	Display::SetColor(Colors::YELLOW);
	if (Level::CanMove())
	{
		Display::WriteLine("1) Move Environment Up");
	}
	Display::WriteLine("2) Rotate Environment Clockwise");
	Display::WriteLine("3) Reset Environment");
	Display::WriteLine("0) Abandon Game");
	Display::WriteLine();
	Display::SetColor(Colors::GRAY);
	Display::WriteText(">");
}

static void Starter()
{
	InputBuffer::Clear();
	Refresh();
}

static void OnCommand(const std::string& command)
{
	if (command == "0")
	{
		Game::SetCurrentState(MainMenu::GetStateId());
	}
	else if (command == "1")
	{
		Level::Move();
		if (Level::IsWinner())
		{
			Level::Draw();
			Display::SetColor(Colors::GRAY);
			Display::WriteLine(std::format("Total Moves: {}", Level::GetMoveCounter()));
			Display::WriteLine();
			Display::SetColor(Colors::GREEN);
			Display::WriteLine("YOU WIN!");
			Game::SetCurrentState(MainMenu::GetStateId());
		}
		else
		{
			Refresh();
		}
	}
	else if (command == "2")
	{
		Level::Rotate();
		Refresh();
	}
	else if (command == "3")
	{
		Level::Reset();
		Refresh();
	}
	else
	{
		Display::SetColor(Colors::RED);
		Display::WriteLine();
		Display::WriteLine("Invalid input!");
		Refresh();
	}
}

static void InputHandler(const std::string& input)
{
	InputBuffer::Append(input, OnCommand);
}

void InPlay::Start()
{
	stateId = Game::RegisterState(Starter, InputHandler);
}