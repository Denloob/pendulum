#include "SDL.h"
#include "main.h"
#include "stdbool.h"
#include "utils.h"

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        die("SDL_Init: %s", SDL_GetError());

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
                                    &renderer) < 0)
        die("SDL_CreateWindowAndRenderer: %s", SDL_GetError());

    SDL_SetWindowTitle(window, WINDOW_NAME);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
    if (!SDL_RenderSetVSync(renderer, true))
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "SDL_RenderSetVSync: %s",
                    SDL_GetError());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
