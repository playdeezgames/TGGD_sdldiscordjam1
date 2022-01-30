#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char** argv)
{
	constexpr auto SCREEN_WIDTH = 1280;
	constexpr auto SCREEN_HEIGHT = 720;
	constexpr auto LOGICAL_WIDTH = 640;
	constexpr auto LOGICAL_HEIGHT = 360;

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
	return 0;
}
