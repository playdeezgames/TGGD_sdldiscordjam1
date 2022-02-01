#include "ConfirmQuit.h"
#include <optional>
#include "Game.h"
#include "InputBuffer.h"
#include "Display.h"
#include "Colors.h"
#include "MainMenu.h"
static std::optional<size_t> stateId{};

size_t ConfirmQuit::GetStateId()
{
	return *stateId;
}

static void Refresh()
{
	Display::WriteLine();
	Display::SetColor(Colors::RED);
	Display::WriteLine("Are you sure you want to quit?");
	Display::SetColor(Colors::YELLOW);
	Display::WriteLine("1) Yes");
	Display::WriteLine("0) No");
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
		Game::SetCurrentState(std::nullopt);
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

void ConfirmQuit::Start()
{
	stateId = Game::RegisterState(Starter, InputHandler);
}