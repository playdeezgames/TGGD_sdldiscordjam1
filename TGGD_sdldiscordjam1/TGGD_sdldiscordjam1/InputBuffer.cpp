#include "InputBuffer.h"
#include "Display.h"
static std::string buffer{};

void InputBuffer::Clear()
{
	buffer.clear();
}

bool InputBuffer::IsEmpty()
{
	return buffer.empty();
}

void InputBuffer::Append(const std::string& text, std::function<void(const std::string&)> processor)
{
	if (text == "\b")
	{
		Backspace();
	}
	else if (text == "\n")
	{
		Display::WriteLine();
		processor(buffer);
		Clear();
	}
	else
	{
		Display::WriteText(text);
		buffer.append(text);
	}
}

const std::string& InputBuffer::Read()
{
	return buffer;
}

void InputBuffer::Backspace()
{
	if (!buffer.empty())
	{
		Display::Backspace();
		buffer.pop_back();
	}
}
