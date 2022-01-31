#include "Display.h"
#include <SDL.h>
#include <SDL_image.h>
static constexpr auto LOGICAL_WIDTH = 640;
static constexpr auto LOGICAL_HEIGHT = 360;
static constexpr auto SCREEN_WIDTH = LOGICAL_WIDTH * 2;
static constexpr auto SCREEN_HEIGHT = LOGICAL_HEIGHT * 2;
static constexpr auto CELL_WIDTH = 8;
static constexpr auto CELL_HEIGHT = 8;
static constexpr auto CELL_COLUMNS = LOGICAL_WIDTH / CELL_WIDTH;
static constexpr auto CELL_ROWS = LOGICAL_HEIGHT / CELL_HEIGHT;

void Display::Run()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetWindowTitle(window, "TGGD_sdldiscordjam1");
	SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

	SDL_Texture* texture = IMG_LoadTexture(renderer, "romfont8x8.png");

	SDL_Event evt{};

	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&evt))
		{
			done = evt.type == SDL_QUIT;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

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