#pragma once

#include "SDL.h"

/**
 * @brief Runs the pendulum simulation. Will block the execution until the end
 *          of the simulation.
 *
 * @param renderer The renderer to use for the simulation.
 */
void pendulum_simulation_run(SDL_Renderer *renderer);
