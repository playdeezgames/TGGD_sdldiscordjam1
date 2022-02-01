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
	"          ##########          ",
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

static void MoveNorth()
{
	for (size_t destinationRow = 0; destinationRow < levelData.size() - 1; ++destinationRow)
	{
		size_t sourceRow = destinationRow + 1;
		for (size_t column = 0; column < levelData[destinationRow].size(); ++column)
		{
			auto& destination = levelData[destinationRow][column];
			auto& source = levelData[sourceRow][column];
			destination.target = source.target;
			destination.occupant = source.occupant;
		}
	}
	for (size_t column = 0; column < levelData.back().size(); ++column)
	{
		levelData.back()[column].target = false;
		levelData.back()[column].occupant = std::nullopt;
	}
}

void Level::Move(const Direction& direction)
{
	if (CanMove(direction))
	{
		switch (direction)
		{
		case Direction::NORTH:
			MoveNorth();
			break;
		}
	}
}

static bool CanMoveNorth()
{
	const auto& row = levelData.front();
	return 
		std::all_of(
			row.begin(), 
			row.end(), 
			[](const auto& cell) 
			{
				return !cell.occupant.has_value() && !cell.target;
			});
}

bool Level::CanMove(const Direction& direction)
{
	return 
		(direction == Direction::NORTH) ? (CanMoveNorth()) :
		(false);
}
