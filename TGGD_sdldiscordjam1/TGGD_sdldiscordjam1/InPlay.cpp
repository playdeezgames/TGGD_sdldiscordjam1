#include "InPlay.h"
#include <optional>
#include "Game.h"
#include "InputBuffer.h"
#include "Level.h"
#include "Display.h"
#include "Colors.h"
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
	Display::WriteLine("1) Move Environment North");
	Display::WriteLine("2) Move Environment East");
	Display::WriteLine("3) Move Environment South");
	Display::WriteLine("4) Move Environment West");
	Display::WriteLine("5) Reset Environment");
	Display::WriteLine("0) Abandon Game");
}

static void Starter()
{
	InputBuffer::Clear();
	Refresh();
}

static void OnCommand(const std::string& command)
{
	Display::SetColor(Colors::RED);
	Display::WriteLine();
	Display::WriteLine("Invalid input!");
	Refresh();
}

static void InputHandler(const std::string& input)
{
	InputBuffer::Append(input, OnCommand);
}

void InPlay::Start()
{
	stateId = Game::RegisterState(Starter, InputHandler);
}