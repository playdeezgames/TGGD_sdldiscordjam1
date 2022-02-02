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
	bool immovable;
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
					cell.immovable = false;
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

void Level::Move()
{
	if (CanMove())
	{
		for (size_t row = 0; row < levelData.size() - 1; ++row)
		{
			for (size_t column = 0; column < levelData[row].size(); ++column)
			{
				auto& cell = levelData[row][column];
				if (cell.occupant.has_value() && *cell.occupant == Occupant::CHARACTER)
				{
					auto& nextCell = levelData[row + 1][column];
					if (!nextCell.occupant.has_value())
					{
						cell.immovable = true;
					}
					else if (*nextCell.occupant == Occupant::BOX)
					{
						auto& thirdCell = levelData[row + 2][column];
						if (!thirdCell.occupant.has_value())
						{
							cell.immovable = true;
							nextCell.immovable = true;
						}
					}
				}
			}
		}
		for (size_t destinationRow = 0; destinationRow < levelData.size() - 1; ++destinationRow)
		{
			size_t sourceRow = destinationRow + 1;
			for (size_t column = 0; column < levelData[destinationRow].size(); ++column)
			{
				auto& destination = levelData[destinationRow][column];
				auto source = levelData[sourceRow][column];
				destination.target = source.target;
				if (!destination.immovable && source.immovable)
				{
					destination.occupant = std::nullopt;
				}
				else if (!destination.immovable && !source.immovable)
				{
					destination.occupant = source.occupant;
				}
			}
		}
		for (size_t column = 0; column < levelData.back().size(); ++column)
		{
			levelData.back()[column].target = false;
			levelData.back()[column].occupant = std::nullopt;
		}
		for (size_t row = 0; row < levelData.size() - 1; ++row)
		{
			for (size_t column = 0; column < levelData[row].size(); ++column)
			{
				levelData[row][column].immovable = false;
			}
		}
	}
}

bool Level::CanMove()
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

void Level::Rotate()
{
	auto oldLevelData = levelData;
	const size_t rows = oldLevelData.size();
	const size_t columns = oldLevelData.front().size();
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t column = 0; column < columns; ++column)
		{
			auto sourceCell = oldLevelData[row][column];
			auto& destinationCell = levelData[column][columns - 1 - row];
			destinationCell.target = sourceCell.target;
			destinationCell.occupant = sourceCell.occupant;
		}
	}
}

bool Level::IsWinner()
{
	return std::all_of(
		levelData.begin(),
		levelData.end(),
		[](const auto& rowData)
		{
			return std::all_of(
				rowData.begin(),
				rowData.end(),
				[](const auto& cell) 
				{
					return 
						!cell.occupant.has_value() || 
						*cell.occupant != Occupant::BOX || 
						cell.target;
				});
		});
}

