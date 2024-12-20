/*
** KORO PROJECT, 2024
** MyDream
** File description:
** window
*/

#include "ray.h"

static const uint8_t WORLD_MAP[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

bool init_sdl(game_state_t *game)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    game->window = SDL_CreateWindow("MyDream", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!game->window)
        return false;

    game->renderer = SDL_CreateRenderer(game->window, -1,
        SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        SDL_DestroyWindow(game->window);
        return false;
    }

    game->mouse_active = false;
    game->window_focused = true;
    game->map = WORLD_MAP;
    return true;
}

void cleanup_sdl(game_state_t *game)
{
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

void handle_window_event(game_state_t *game, SDL_Event *event)
{
    switch (event->window.event) {
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            game->window_focused = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            game->window_focused = false;
            game->mouse_active = false;
            SDL_SetRelativeMouseMode(SDL_FALSE);
            break;
    }
}
