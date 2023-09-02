#pragma once

#include "SDL.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define WINDOW_NAME "Pendulum Simulation"

/**
 * @brief Initializes the given window and renderer with default parameters,
 *          with WINDOW_{WIDTH,HEIGHT,NAME}, in the center and with VSync
 *          enabled.
 *
 * @param window_ptr Pointer to the SDL window to initialize
 * @param renderer_ptr Pointer to the SDL renderer to initialize
 *
 * @see quit_sdl
 */
void init_sdl(SDL_Window **window_ptr, SDL_Renderer **renderer_ptr);

/**
 * @brief Destroys the given window and renderer.and quits SDL.
 *
 * @param window The SDL window to destroy
 * @param renderer The SDL renderer to destroy
 *
 * @see init_sdl
 */
void quit_sdl(SDL_Window *window, SDL_Renderer *renderer);
