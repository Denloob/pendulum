#pragma once

#include "SDL.h"

#define PENDULUM_BOB_RADIUS 20
#define PENDULUM_BOB_COLOR ((SDL_Color){0x85, 0x89, 0xCC, SDL_ALPHA_OPAQUE})
#define PENDULUM_ARM_LENGTH 200
#define PENDULUM_ARM_COLOR ((SDL_Color){0xA0, 0x99, 0xBB, SDL_ALPHA_OPAQUE})
#define PENDULUM_STARTING_ANGLE M_PI / 6

#define GRAVITY 0.7

typedef struct Pendulum
{
    SDL_FPoint pos;
    float arm_angle;
    float arm_length;
    float bob_radius;
    float rotational_velocity;
    SDL_Color bob_color;
    SDL_Color arm_color;
} Pendulum;

/**
 * @brief Creates a pendulum.
 *
 * @param pos The pivot of the pendulum.
 * @param length The length of pendulum's arm.
 * @param arm_color The color of the pendulum's arm.
 * @param bob_radius The radius of pendulum's bob.
 * @param bob_color The color of pendulum's bob.
 * @param starting_angle The starting angle of pendulum's arm.
 * @return The created pendulum.
 *
 * @see pendulum_destroy
 */
Pendulum *pendulum_create(SDL_FPoint pos, float length, SDL_Color arm_color,
                          float bob_radius, SDL_Color bob_color,
                          float starting_angle);

/**
 * @brief Creates a default pendulum for the given window.
 *
 * @param window The SDL window where the pendulum is intended to be used.
 * @return The created pendulum.
 *
 * @see pendulum_create
 * @see pendulum_destroy
 */
Pendulum *pendulum_create_default_for(SDL_Window *window);

/**
 * @brief Destroys the given pendulum.
 *
 * @see pendulum_create
 */
void pendulum_destroy(Pendulum *pendulum);

/**
 * @brief Draws the pendulum.
 */
void pendulum_draw(Pendulum *pendulum, SDL_Renderer *renderer);

/**
 * @brief Ticks pendulum's state.
 */
void pendulum_tick(Pendulum *pendulum);

/**
 * @brief Runs the pendulum simulation. Will block the execution until the end
 *          of the simulation.
 *
 * @param window The SDL window for displaying the pendulum simulation.
 */
void pendulum_simulation_run(SDL_Window *window);
