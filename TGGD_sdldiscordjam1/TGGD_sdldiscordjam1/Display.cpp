#include "Display.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include "Game.h"
static constexpr auto LOGICAL_WIDTH = 640;
static constexpr auto LOGICAL_HEIGHT = 360;
static constexpr auto SCREEN_WIDTH = LOGICAL_WIDTH * 2;
static constexpr auto SCREEN_HEIGHT = LOGICAL_HEIGHT * 2;
static constexpr auto CELL_WIDTH = 8;
static constexpr auto CELL_HEIGHT = 8;
static constexpr auto CELL_COLUMNS = LOGICAL_WIDTH / CELL_WIDTH;
static constexpr auto CELL_ROWS = LOGICAL_HEIGHT / CELL_HEIGHT;
static constexpr auto WINDOW_TILE = "TGGD_sdldiscordjam1";
static constexpr auto TEXTURE_FILE_NAME = "romfont8x8.png";
static constexpr auto TEXTURE_COLUMNS = 16;
static constexpr auto TEXTURE_ROWS = 16;

struct DisplayCell
{
	DisplayCell(const std::tuple<Uint8, Uint8, Uint8>& color, char character)
		: color(color)
		, character(character) {}
	std::tuple<Uint8, Uint8, Uint8> color;
	char character;
};

static SDL_Renderer* renderer = nullptr;
static SDL_Texture* texture = nullptr;
static std::map<char, SDL_Rect> textureCellRects{};
static std::vector<SDL_Rect> displayCellRects{};
static size_t currentPosition{};
static std::tuple<Uint8, Uint8, Uint8> currentColor = std::make_tuple<Uint8, Uint8, Uint8>(255,255,255);
static std::vector<DisplayCell> displayCells{};

static void InitializeTextureCellRects()
{
	textureCellRects.clear();
	char character = 0;
	for (int row = 0; row < TEXTURE_ROWS; ++row)
	{
		for (int column = 0; column < TEXTURE_COLUMNS; ++column)
		{
			textureCellRects.emplace(
				std::make_pair(
					character++, 
					SDL_Rect{ column * CELL_WIDTH, row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT })
			);
		}
	}
}

static void InitializeDisplayCellRects()
{
	displayCellRects.clear();
	for (int row = 0; row < CELL_ROWS; ++row)
	{
		for (int column = 0; column < CELL_COLUMNS; ++column)
		{
			displayCellRects.emplace_back(SDL_Rect{ column * CELL_WIDTH, row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
		}
	}
}

static void InitializeDisplayCells()
{
	displayCells.clear();
	for (int row = 0; row < CELL_ROWS; ++row)
	{
		for (int column = 0; column < CELL_COLUMNS; ++column)
		{
			displayCells.emplace_back(std::make_tuple<Uint8,Uint8,Uint8>(0,0,0), '\0');
		}
	}
}

void Display::Run()
{
	InitializeTextureCellRects();
	InitializeDisplayCellRects();
	InitializeDisplayCells();

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = nullptr;

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetWindowTitle(window, WINDOW_TILE);
	SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

	texture = IMG_LoadTexture(renderer, TEXTURE_FILE_NAME);

	Game::Start();

	SDL_Event evt{};

	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_TEXTINPUT:
				Game::HandleInput(evt.text.text);
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		Game::Update();
		SDL_RenderClear(renderer);
		for (size_t index = 0; index < displayCells.size(); ++index)
		{
			auto color = displayCells.at(index).color;
			auto character = displayCells.at(index).character;
			SDL_SetTextureColorMod(texture, std::get<0>(color), std::get<1>(color), std::get<2>(color));
			SDL_RenderCopy(renderer, texture, &textureCellRects.at(character), &displayCellRects.at(index));
		}
		SDL_RenderPresent(renderer);
	}

	Game::Finish();

	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
	if (window)
	{
		SDL_DestroyWindow(window);
	}
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
	}

	IMG_Quit();
	SDL_Quit();
}

void Display::WriteCharacter(char character)
{
	displayCells[currentPosition] = DisplayCell(currentColor, character);
	currentPosition++;
	currentPosition %= displayCells.size();
}
