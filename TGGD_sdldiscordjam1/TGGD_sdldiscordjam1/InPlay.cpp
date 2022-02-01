#include "InPlay.h"
#include <optional>
#include "Game.h"
#include "InputBuffer.h"
#include "Level.h"
#include "Display.h"
#include "Colors.h"
#include "MainMenu.h"
static std::optional<size_t> stateId{};

size_t InPlay::GetStateId()
{
	return stateId.value();
}

static void Refresh()
{
	Level::Draw();
	Display::WriteLine();
	Display::SetColor(Colors::YELLOW);
	if (Level::CanMove(Direction::NORTH))
	{
		Display::WriteLine("1) Move Environment North");
	}
	if (Level::CanMove(Direction::EAST))
	{
		Display::WriteLine("2) Move Environment East");
	}
	if (Level::CanMove(Direction::SOUTH))
	{
		Display::WriteLine("3) Move Environment South");
	}
	if (Level::CanMove(Direction::WEST))
	{
		Display::WriteLine("4) Move Environment West");
	}
	Display::WriteLine("5) Reset Environment");
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
		Level::Move(Direction::NORTH);
		Refresh();
	}
	else if (command == "5")
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