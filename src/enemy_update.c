/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Enemy update functions implementation
*/

#include "enemy.h"
#include "player.h"
#include "map.h"
#include <math.h>

void update_enemies(void)
{
    uint32_t current_time = SDL_GetTicks();
    int alive_count = 0;

    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].is_alive)
            continue;
        alive_count++;
        double delta_time = (current_time - enemies[i].last_move_time) / 1000.0;
        enemies[i].last_move_time = current_time;
        double dx = player.x - enemies[i].x;
        double dy = player.y - enemies[i].y;
        double dist = sqrt(dx * dx + dy * dy);
        double min_dist = (enemies[i].type == ENEMY_TOUGH) ? 1.5 : 1.0;

        if (dist > min_dist) {
            dx /= dist;
            dy /= dist;
            if (enemies[i].type == ENEMY_FAST) {
                dx += (rand() % 100 - 50) / 500.0;
                dy += (rand() % 100 - 50) / 500.0;
            }
            double new_x = enemies[i].x + dx * enemies[i].speed * delta_time;
            double new_y = enemies[i].y + dy * enemies[i].speed * delta_time;
            if (map[(int)new_x][(int)enemies[i].y] == 0)
                enemies[i].x = new_x;
            if (map[(int)enemies[i].x][(int)new_y] == 0)
                enemies[i].y = new_y;
        }
        enemies[i].angle = atan2(dy, dx) * 180.0 / M_PI;
    }
    if (alive_count < 5)
        spawn_enemy_wave(15 + rand() % 10);
}
