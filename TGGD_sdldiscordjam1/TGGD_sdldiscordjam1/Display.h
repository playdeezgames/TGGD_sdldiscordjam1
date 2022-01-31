#pragma once
#include <tuple>
#include <string>
struct Display
{
	Display() = delete;
	static void Run();
	static void WriteCharacter(char character);
	static void Backspace();
	static void WriteText(const std::string& text);
	static void WriteLine(const std::string& text = " ");
	static void SetColor(const std::tuple<uint8_t, uint8_t, uint8_t>& color);
	static void SetColor(uint8_t r, uint8_t g, uint8_t b);
};