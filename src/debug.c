/*
** KORO PROJECT, 2024
** MyDream
** File description:
** debug
*/

#include "ray.h"

static void draw_debug_grid(game_state_t *game)
{
    const int CELL_SIZE = 32;
    const int GRID_X = 10;
    const int GRID_Y = 10;

    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);

    for (int x = 0; x <= MAP_WIDTH; x++) {
        SDL_RenderDrawLine(game->renderer,
            GRID_X + x * CELL_SIZE,
            GRID_Y,
            GRID_X + x * CELL_SIZE,
            GRID_Y + MAP_HEIGHT * CELL_SIZE);
    }

    for (int y = 0; y <= MAP_HEIGHT; y++) {
        SDL_RenderDrawLine(game->renderer,
            GRID_X,
            GRID_Y + y * CELL_SIZE,
            GRID_X + MAP_WIDTH * CELL_SIZE,
            GRID_Y + y * CELL_SIZE);
    }
}

static void draw_debug_walls(game_state_t *game)
{
    const int CELL_SIZE = 32;
    const int GRID_X = 10;
    const int GRID_Y = 10;
    SDL_Rect wall;

    SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
    wall.w = CELL_SIZE;
    wall.h = CELL_SIZE;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (game->map[y][x]) {
                wall.x = GRID_X + x * CELL_SIZE;
                wall.y = GRID_Y + y * CELL_SIZE;
                SDL_RenderFillRect(game->renderer, &wall);
            }
        }
    }
}

void draw_debug_ray(game_state_t *game, ray_t *ray)
{
    const int CELL_SIZE = 32;
    const int GRID_X = 10;
    const int GRID_Y = 10;
    
    int start_x = GRID_X + (int)(game->player.pos.x * CELL_SIZE);
    int start_y = GRID_Y + (int)(game->player.pos.y * CELL_SIZE);
    int end_x = GRID_X + ray->map_x * CELL_SIZE + CELL_SIZE / 2;
    int end_y = GRID_Y + ray->map_y * CELL_SIZE + CELL_SIZE / 2;

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(game->renderer, start_x, start_y, end_x, end_y);
}

void draw_debug_player(game_state_t *game)
{
    const int CELL_SIZE = 32;
    const int GRID_X = 10;
    const int GRID_Y = 10;
    const int PLAYER_SIZE = 8;

    int player_x = GRID_X + (int)(game->player.pos.x * CELL_SIZE);
    int player_y = GRID_Y + (int)(game->player.pos.y * CELL_SIZE);

    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    SDL_Rect player_rect = {
        player_x - PLAYER_SIZE/2,
        player_y - PLAYER_SIZE/2,
        PLAYER_SIZE,
        PLAYER_SIZE
    };
    SDL_RenderFillRect(game->renderer, &player_rect);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(game->renderer,
        player_x,
        player_y,
        player_x + (int)(game->player.dir.x * CELL_SIZE),
        player_y + (int)(game->player.dir.y * CELL_SIZE));
}

void render_debug_info(game_state_t *game)
{
    if (!game->debug_mode)
        return;

    draw_debug_grid(game);
    draw_debug_walls(game);
    draw_debug_player(game);
}

/**
FPS counter
Player coordinates
Ray collision points
Distance measurements
**/