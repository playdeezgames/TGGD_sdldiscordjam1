#include "Display.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
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


static SDL_Renderer* renderer = nullptr;
static SDL_Texture* texture = nullptr;
static std::vector<SDL_Rect> textureCells{};
static std::vector<SDL_Rect> displayCells{};
static size_t cursorPosition{};

static void InitializeTextureCells()
{
	textureCells.clear();
	for (int row = 0; row < TEXTURE_ROWS; ++row)
	{
		for (int column = 0; column < TEXTURE_COLUMNS; ++column)
		{
			textureCells.emplace_back(SDL_Rect{ column * CELL_WIDTH, row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
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
			displayCells.emplace_back(SDL_Rect{ column * CELL_WIDTH, row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
		}
	}
}

void Display::Run()
{
	InitializeTextureCells();
	InitializeDisplayCells();

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = nullptr;

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetWindowTitle(window, WINDOW_TILE);
	SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

	texture = IMG_LoadTexture(renderer, TEXTURE_FILE_NAME);

	//game setup

	SDL_Event evt{};

	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&evt))
		{
			done = evt.type == SDL_QUIT;
			//game event handling
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		//game rendering
		SDL_RenderPresent(renderer);
	}

	//game cleanup

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