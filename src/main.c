#include "SDL.h"
#include "main.h"
#include "pendulum.h"
#include "utils.h"

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    init_sdl(&window, &renderer);
    pendulum_simulation_run(window);
    quit_sdl(window, renderer);

    return EXIT_SUCCESS;
}

void init_sdl(SDL_Window **window_ptr, SDL_Renderer **renderer_ptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        die("SDL_Init: %s", SDL_GetError());

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, window_ptr,
                                    renderer_ptr) < 0)
        die("SDL_CreateWindowAndRenderer: %s", SDL_GetError());

    SDL_SetWindowTitle(*window_ptr, WINDOW_NAME);
    SDL_SetWindowPosition(*window_ptr, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
    if (!SDL_RenderSetVSync(*renderer_ptr, true))
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "SDL_RenderSetVSync: %s",
                    SDL_GetError());
}

void quit_sdl(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
