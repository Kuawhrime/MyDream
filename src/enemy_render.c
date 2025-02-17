/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Enemy rendering implementation
*/

#include "enemy.h"
#include "player.h"
#include "map.h"
#include "engine.h"
#include <math.h>

bool check_enemy_visibility(int enemy_idx)
{
    double dir_x = enemies[enemy_idx].x - player.x;
    double dir_y = enemies[enemy_idx].y - player.y;
    double dist_to_enemy = sqrt(dir_x * dir_x + dir_y * dir_y);

    dir_x /= dist_to_enemy;
    dir_y /= dist_to_enemy;
    double ray_length = 0;
    double step_size = 0.1;

    while (ray_length < dist_to_enemy) {
        double check_x = player.x + dir_x * ray_length;
        double check_y = player.y + dir_y * ray_length;
        if (map[(int)check_x][(int)check_y] != 0)
            return false;
        ray_length += step_size;
    }
    return true;
}

void draw_enemy_sprite(int enemy_idx, double angle, double distance)
{
    int screen_x = (int)((SCREEN_WIDTH / 2) *
        (1 + angle / (FOV * M_PI / 180.0 / 2)));
    int height = (int)(SCREEN_HEIGHT / distance);

    if (height > SCREEN_HEIGHT)
        height = SCREEN_HEIGHT;
    int draw_start = SCREEN_HEIGHT / 2 - height / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = draw_start + height;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    SDL_Rect src_rect = {0, 0, TEX_SIZE, TEX_SIZE};
    SDL_Rect dest_rect = {
        screen_x - height / 4,
        draw_start,
        height / 2,
        height
    };
    int brightness = (int)(255 * (1.0 - (distance / MAX_RAY_DEPTH)));

    brightness = (brightness < 0) ? 0 : (brightness > 255 ? 255 : brightness);
    if (enemy_textures[enemies[enemy_idx].type]) {
        SDL_SetTextureColorMod(enemy_textures[enemies[enemy_idx].type],
            brightness, brightness, brightness);
        SDL_RenderCopy(renderer, enemy_textures[enemies[enemy_idx].type],
            &src_rect, &dest_rect);
    } else {
        SDL_SetRenderDrawColor(renderer,
            enemies[enemy_idx].color.r,
            enemies[enemy_idx].color.g,
            enemies[enemy_idx].color.b,
            255);
        SDL_RenderFillRect(renderer, &dest_rect);
    }
}

void render_enemies(void)
{
    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].is_alive)
            continue;
        double dx = enemies[i].x - player.x;
        double dy = enemies[i].y - player.y;
        double distance = sqrt(dx * dx + dy * dy);
        double angle = atan2(dy, dx) - player.angle * M_PI / 180.0;

        if (angle < -M_PI)
            angle += 2 * M_PI;
        if (angle > M_PI)
            angle -= 2 * M_PI;
        if (fabs(angle) > FOV * M_PI / 180.0 / 2.0)
            continue;
        if (!check_enemy_visibility(i))
            continue;
        draw_enemy_sprite(i, angle, distance);
    }
}
