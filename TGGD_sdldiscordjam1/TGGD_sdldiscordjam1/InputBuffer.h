#pragma once
#include <string>
#include <functional>
struct InputBuffer
{
	InputBuffer() = delete;
	static void Clear();
	static bool IsEmpty();
	static void Append(const std::string& text, std::function<void(const std::string&)> processor);
	static const std::string& Read();
	static void Backspace();
};
