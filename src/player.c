/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Player implementation
*/

#include "player.h"
#include "map.h"
#include "engine.h"
#include "menu.h"
#include <stdio.h>

player_t player = {4, 4, 0};

bool is_valid_position(double x, double y)
{
    int int_x = (int)x;
    int int_y = (int)y;

    return (int_x >= 0 && int_x < MAP_WIDTH &&
        int_y >= 0 && int_y < MAP_HEIGHT);
}

void move_player(double delta_x, double delta_y)
{
    double new_x = player.x + delta_x;
    double new_y = player.y + delta_y;

    if (!is_valid_position(new_x, new_y))
        return;
    if (map[(int)new_x][(int)player.y] == 0)
        player.x = new_x;
    if (map[(int)player.x][(int)new_y] == 0)
        player.y = new_y;
}

void handle_input(void)
{
    static uint32_t last_time = 0;
    uint32_t current_time = SDL_GetTicks();
    float delta_time = (current_time - last_time) / 1000.0f;
    const uint8_t *keys = SDL_GetKeyboardState(NULL);
    double move_speed = 3.0 * delta_time;

    if (game_paused)
        return;
    last_time = current_time;

    if (keys[SDL_SCANCODE_A])
        player.angle -= 2.0;
    if (keys[SDL_SCANCODE_D])
        player.angle += 2.0;
    
    if (player.angle < 0)
        player.angle += 360;
    if (player.angle >= 360)
        player.angle -= 360;

    if (keys[SDL_SCANCODE_W])
        move_player(cos(player.angle * M_PI / 180.0) * move_speed,
            sin(player.angle * M_PI / 180.0) * move_speed);
    if (keys[SDL_SCANCODE_S])
        move_player(-cos(player.angle * M_PI / 180.0) * move_speed,
            -sin(player.angle * M_PI / 180.0) * move_speed);

    if (keys[SDL_SCANCODE_M] && !game_paused)
        show_map = !show_map;
}