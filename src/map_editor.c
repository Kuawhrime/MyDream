/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Map editor implementation
*/

#include "map_editor.h"
#include "map.h"
#include "engine.h"
#include "player.h"

static bool is_valid_map_position(int x, int y)
{
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

void draw_map_editor(void)
{
    if (!show_map)
        return;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile = {
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            switch (map[x][y]) {
                case 1:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
                    break;
                case 4:
                    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect player_rect = {
        (int)(player.x * TILE_SIZE) - 4,
        (int)(player.y * TILE_SIZE) - 4,
        8,
        8
    };
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int start_x = (int)(player.x * TILE_SIZE);
    int start_y = (int)(player.y * TILE_SIZE);
    int end_x = start_x + cos(player.angle * M_PI / 180.0) * 20;
    int end_y = start_y + sin(player.angle * M_PI / 180.0) * 20;
    SDL_RenderDrawLine(renderer, start_x, start_y, end_x, end_y);
}

void handle_map_editor_input(void)
{
    int mouse_x;
    int mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    int tile_x = mouse_x / TILE_SIZE;
    int tile_y = mouse_y / TILE_SIZE;

    if (!is_valid_map_position(tile_x, tile_y))
        return;
    Uint32 buttons = SDL_GetMouseState(NULL, NULL);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        map[tile_x][tile_y] = 1;
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
        map[tile_x][tile_y] = 0;
}