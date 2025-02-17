/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Enemy system implementation
*/

#include "enemy.h"
#include "player.h"
#include "map.h"
#include "engine.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

enemy_t enemies[MAX_ENEMIES];
SDL_Texture *enemy_textures[ENEMY_TYPES] = {NULL};
int enemy_count = 0;

static bool load_enemy_textures(void)
{
    const char *texture_paths[ENEMY_TYPES] = {
        "assets/textures/barack.png",
        "assets/textures/steve-harvey.png",
        "assets/textures/josh.png"
    };
    bool success = true;

    for (int i = 0; i < ENEMY_TYPES; i++) {
        SDL_Surface *surface = IMG_Load(texture_paths[i]);
        if (!surface) {
            printf("Failed to load enemy texture %s: %s\n",
                texture_paths[i], IMG_GetError());
            success = false;
            continue;
        }
        enemy_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!enemy_textures[i]) {
            printf("Failed to create enemy texture: %s\n", SDL_GetError());
            success = false;
        }
    }
    return success;
}

static void init_enemy_props(enemy_t *enemy, enemy_type_t type)
{
    switch (type) {
        case ENEMY_FAST:
            enemy->health = 50;
            enemy->speed = 2.5;
            enemy->color = (SDL_Color){255, 0, 0, 255};
            break;
        case ENEMY_TOUGH:
            enemy->health = 200;
            enemy->speed = 1.0;
            enemy->color = (SDL_Color){0, 0, 255, 255};
            break;
        default:
            enemy->health = 100;
            enemy->speed = 1.5;
            enemy->color = (SDL_Color){0, 255, 0, 255};
    }
}

void spawn_enemy(double x, double y, enemy_type_t type)
{
    if (enemy_count >= MAX_ENEMIES)
        return;
    enemies[enemy_count].x = x;
    enemies[enemy_count].y = y;
    enemies[enemy_count].is_alive = true;
    enemies[enemy_count].angle = 0;
    enemies[enemy_count].last_move_time = SDL_GetTicks();
    enemies[enemy_count].type = type;
    init_enemy_props(&enemies[enemy_count], type);
    enemy_count++;
}

void spawn_enemy_wave(int count)
{
    for (int i = 0; i < count && enemy_count < MAX_ENEMIES; i++) {
        int side = rand() % 4;
        double x = 0;
        double y = 0;

        switch (side) {
            case 0:
                x = 2 + rand() % (MAP_WIDTH - 4);
                y = 2;
                break;
            case 1:
                x = MAP_WIDTH - 3;
                y = 2 + rand() % (MAP_HEIGHT - 4);
                break;
            case 2:
                x = 2 + rand() % (MAP_WIDTH - 4);
                y = MAP_HEIGHT - 3;
                break;
            case 3:
                x = 2;
                y = 2 + rand() % (MAP_HEIGHT - 4);
        }
        spawn_enemy(x, y, rand() % ENEMY_TYPES);
    }
}

void init_enemies(void)
{
    srand(time(NULL));
    enemy_count = 0;
    if (!load_enemy_textures())
        printf("WHERE IS ENEMY TEXTURE ????\n");
    spawn_enemy_wave(20);
}

void check_enemy_hits(double start_x, double start_y,
    double dir_x, double dir_y, double range, int damage)
{
    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].is_alive)
            continue;
        double to_enemy_x = enemies[i].x - start_x;
        double to_enemy_y = enemies[i].y - start_y;
        double dist_to_enemy = sqrt(to_enemy_x * to_enemy_x +
            to_enemy_y * to_enemy_y);

        if (dist_to_enemy <= range) {
            double dot = (dir_x * to_enemy_x + dir_y * to_enemy_y) / dist_to_enemy;
            double angle = acos(dot) * 180.0 / M_PI;

            if (angle <= 30.0) {
                enemies[i].health -= damage;
                printf("Enemy hit! Type: %d, Health: %d\n",
                    enemies[i].type, enemies[i].health);
                if (enemies[i].health <= 0) {
                    enemies[i].is_alive = false;
                    printf("Enemy killed!\n");
                }
            }
        }
    }
}

void draw_enemies(void)
{
    if (!show_map)
        return;
    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].is_alive)
            continue;
        SDL_SetRenderDrawColor(renderer,
            enemies[i].color.r,
            enemies[i].color.g,
            enemies[i].color.b,
            255);
        SDL_Rect enemy_rect = {
            (int)(enemies[i].x * TILE_SIZE) - 4,
            (int)(enemies[i].y * TILE_SIZE) - 4,
            8,
            8
        };
        SDL_RenderFillRect(renderer, &enemy_rect);

        int start_x = (int)(enemies[i].x * TILE_SIZE);
        int start_y = (int)(enemies[i].y * TILE_SIZE);
        int end_x = start_x + cos(enemies[i].angle * M_PI / 180.0) * 8;
        int end_y = start_y + sin(enemies[i].angle * M_PI / 180.0) * 8;
        SDL_RenderDrawLine(renderer, start_x, start_y, end_x, end_y);
    }
}