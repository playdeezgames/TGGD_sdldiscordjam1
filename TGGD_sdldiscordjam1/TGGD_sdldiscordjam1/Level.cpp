#include "Level.h"
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <iterator>
#include "Display.h"
#include "Colors.h"

static const std::vector<std::string> rawLevelData =
{
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"          ##########          ",
	"          #       ##          ",
	"          # $    ###          ",
	"          #. ## . ##          ",
	"          # ####  ##          ",
	"          #   #   ##          ",
	"          #$$ #. ###          ",
	"          # # # $@##          ",
	"          # .    ###          ",
	"          ##########          "
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              "
};

enum class Occupant
{
	WALL,
	BOX,
	CHARACTER
};

struct LevelCell
{
	bool target;
	std::optional<Occupant> occupant;
};

static std::vector<std::vector<LevelCell>> levelData{};

void Level::Reset()
{
	levelData.clear();
	std::transform(
		rawLevelData.begin(), 
		rawLevelData.end(),
		std::back_inserter(levelData),
		[](const auto& line) 
		{
			std::vector<LevelCell> result{};
			std::transform(
				line.begin(), 
				line.end(), 
				std::back_inserter(result), 
				[](auto character) 
				{
					LevelCell cell{};
					cell.target = (character == '.' || character == '*');
					cell.occupant =
						(character == '@') ? (std::optional<Occupant>(Occupant::CHARACTER)) :
						(character == '#') ? (std::optional<Occupant>(Occupant::WALL)) :
						(character == '$') ? (std::optional<Occupant>(Occupant::BOX)) :
						(character == '*') ? (std::optional<Occupant>(Occupant::BOX)) :
						(std::nullopt);
					return cell;
				});
			return result;
		});
}

static void DrawLevelCell(const LevelCell& cell)
{
	if (cell.occupant)
	{
		switch (*cell.occupant)
		{
		case Occupant::WALL:
			Display::SetColor(Colors::BLUE);
			Display::WriteCharacter('#');
			break;
		case Occupant::CHARACTER:
			Display::SetColor(Colors::WHITE);
			Display::WriteCharacter('@');
			break;
		case Occupant::BOX:
			if (cell.target)
			{
				Display::SetColor(Colors::GREEN);
				Display::WriteCharacter('*');
			}
			else
			{
				Display::SetColor(Colors::RED);
				Display::WriteCharacter('$');
			}
			break;
		}
	}
	else
	{
		if (cell.target)
		{
			Display::SetColor(Colors::YELLOW);
			Display::WriteCharacter('.');
		}
		else
		{
			Display::WriteCharacter(' ');
		}
	}
}

void Level::Draw()
{
	std::for_each(
		levelData.begin(), 
		levelData.end(), 
		[](const auto& row) 
		{
			std::for_each(
				row.begin(), 
				row.end(), 
				DrawLevelCell);
			Display::WriteLine();
		});
}

void Level::Move(const Direction& direction)
{

}

bool Level::CanMove(const Direction& direction)
{
	return false;
}
