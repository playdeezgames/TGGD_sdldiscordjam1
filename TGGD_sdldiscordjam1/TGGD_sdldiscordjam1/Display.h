#pragma once
#include <tuple>
#include <string>
struct Display
{
	Display() = delete;
	static void Run();
	static void WriteCharacter(char character);
	static void WriteText(const std::string& text);
	static void WriteLine(const std::string& text = "");
	static void SetColor(uint8_t r, uint8_t g, uint8_t b);
};