#include "SDL.h"
#include "SDL2_framerate.h"
#include "SDL2_gfxPrimitives.h"
#include "pendulum.h"
#include "utils.h"

/**
 * @brief Draws the bob of the pendulum.
 *
 * @param renderer The renderer to draw onto.
 * @param bob_position The point where bob's center is currently located.
 */
static void pendulum_draw_bob(Pendulum *pendulum, SDL_Renderer *renderer,
                              SDL_FPoint arm_position);

/**
 * @brief Draws the arm of the pendulum.
 *
 * @param renderer The renderer to draw onto.
 * @param bob_position The point where bob's center is currently located.
 */
static void pendulum_draw_arm(Pendulum *pendulum, SDL_Renderer *renderer,
                              SDL_FPoint arm_position);

/**
 * @brief Calculates the position of bob's center.
 *
 * @return The position of bob's center.
 */
static SDL_FPoint pendulum_calculate_bob_position(Pendulum *pendulum);

void pendulum_simulation_run(SDL_Window *window)
{
    Pendulum *pendulum = pendulum_create_default_for(window);
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    if (!renderer)
        die("SDL_GetRenderer: %s", SDL_GetError());

    FPSmanager fps_manager = {0};
    SDL_initFramerate(&fps_manager);

    bool done = false;
    while (!done)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = true;
        }

        pendulum_tick(pendulum);
        pendulum_draw(pendulum, renderer);

        SDL_RenderPresent(renderer);
        SDL_framerateDelay(&fps_manager);
    }

    pendulum_destroy(pendulum);
}

void pendulum_tick(Pendulum *pendulum)
{
    float pendulum_force = -sin(pendulum->arm_angle) * GRAVITY / pendulum->arm_length;
    pendulum->rotational_velocity += pendulum_force;
    pendulum->arm_angle += pendulum->rotational_velocity;
}

Pendulum *pendulum_create(SDL_FPoint pos, float length, SDL_Color arm_color,
                          float bob_radius, SDL_Color bob_color,
                          float starting_angle)
{
    Pendulum *pendulum = xmalloc(sizeof(*pendulum));
    pendulum->pos = pos;
    pendulum->rotational_velocity = 0;
    pendulum->arm_angle = starting_angle;
    pendulum->arm_length = length;
    pendulum->arm_color = arm_color;
    pendulum->bob_radius = bob_radius;
    pendulum->bob_color = bob_color;

    return pendulum;
}

Pendulum *pendulum_create_default_for(SDL_Window *window)
{

    SDL_Point screen_size = {0};
    SDL_GetWindowSize(window, &screen_size.x, &screen_size.y);
    SDL_FPoint pendulum_pivot_pos = {
        screen_size.x / 2.0,
        (screen_size.y - PENDULUM_ARM_LENGTH) / 2.0,
    };

    return pendulum_create(pendulum_pivot_pos, PENDULUM_ARM_LENGTH,
                           PENDULUM_ARM_COLOR, PENDULUM_BOB_RADIUS,
                           PENDULUM_BOB_COLOR, PENDULUM_STARTING_ANGLE);
}

void pendulum_destroy(Pendulum *pendulum)
{
    free(pendulum);
}

static SDL_FPoint pendulum_calculate_bob_position(Pendulum *pendulum)
{

    float arm_length = pendulum->arm_length;
    float arm_angle = pendulum->arm_angle;
    SDL_FPoint bob_position = {arm_length * sin(arm_angle),
                               arm_length * cos(arm_angle)};

    bob_position.x += pendulum->pos.x;
    bob_position.y += pendulum->pos.y;

    return bob_position;
}

void pendulum_draw(Pendulum *pendulum, SDL_Renderer *renderer)
{
    SDL_FPoint bob_position = pendulum_calculate_bob_position(pendulum);

    pendulum_draw_arm(pendulum, renderer, bob_position);
    pendulum_draw_bob(pendulum, renderer, bob_position);
}

static void pendulum_draw_bob(Pendulum *pendulum, SDL_Renderer *renderer,
                              SDL_FPoint bob_position)
{
    SDL_Color color = pendulum->bob_color;

    filledCircleRGBA(renderer, bob_position.x, bob_position.y, pendulum->bob_radius,
               color.r, color.g, color.b, color.a);
}

static void pendulum_draw_arm(Pendulum *pendulum, SDL_Renderer *renderer,
                              SDL_FPoint arm_position)
{
    SDL_Color color = pendulum->arm_color;

    lineRGBA(renderer, pendulum->pos.x, pendulum->pos.y, arm_position.x,
             arm_position.y, color.r, color.g, color.b, color.a);
}
