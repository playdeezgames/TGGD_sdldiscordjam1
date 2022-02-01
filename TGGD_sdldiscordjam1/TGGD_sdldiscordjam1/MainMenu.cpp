#include "MainMenu.h"
#include "Game.h"
#include "Display.h"
#include "Colors.h"
#include "InputBuffer.h"

static std::optional<size_t> stateId{};

size_t MainMenu::GetStateId()
{
	return *stateId;
}

static void Refresh()
{
	Display::WriteLine();
	Display::SetColor(Colors::GREEN);
	Display::WriteLine("Main Menu:");
	Display::SetColor(Colors::YELLOW);
	Display::WriteLine("0) Quit");
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

void MainMenu::Start()
{
	stateId = Game::RegisterState(Starter, InputHandler);
}