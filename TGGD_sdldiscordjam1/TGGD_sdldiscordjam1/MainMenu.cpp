#include "MainMenu.h"
#include "Game.h"
#include "Display.h"
#include "Colors.h"

static std::optional<size_t> stateId{};
static std::string buffer = "";

size_t MainMenu::GetStateId()
{
	return *stateId;
}

static void Starter()
{
	Display::WriteLine();
	Display::SetColor(Colors::GREEN);
	Display::WriteLine("Main Menu:");
	Display::SetColor(Colors::YELLOW);
	Display::WriteLine("0) Quit");
	Display::WriteLine();
	Display::SetColor(Colors::GRAY);
	Display::WriteText(">");
	buffer = "";
}

static void Updater()
{

}

static void InputHandler(const std::string& input)
{
	Display::WriteText(input);
	buffer += input;
}

void MainMenu::Start()
{
	stateId = Game::RegisterState(Starter, Updater, InputHandler);
}