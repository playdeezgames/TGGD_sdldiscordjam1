#pragma once
#include <tuple>
struct Display
{
	Display() = delete;
	static void Run();
	static void WriteCharacter(char character);
	static void SetColor(uint8_t r, uint8_t g, uint8_t b);
};