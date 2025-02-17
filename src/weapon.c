/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Weapon system implementation
*/

#include "weapon.h"
#include "enemy.h"
#include "player.h"
#include "engine.h"
#include "sound.h"
#include <stdio.h>

weapon_t current_weapon = {
    .damage = 25,
    .range = 8.0,
    .ammo = 30,
    .max_ammo = 30,
    .last_shot_time = 0,
    .fire_rate = 0.1,
    .weapon_texture = NULL,
    .is_firing = false,
    .current_frame = 0,
    .total_frames = 3
};

void init_weapon(void)
{
    const char *weapon_path = "assets/textures/weapon.png";
    SDL_Surface *surface = IMG_Load(weapon_path);

    if (!surface) {
        printf("Failed to load weapon texture: %s\nPath: %s\n",
            IMG_GetError(), weapon_path);
        return;
    }
    current_weapon.weapon_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!current_weapon.weapon_texture) {
        printf("Failed to create weapon texture: %s\n", SDL_GetError());
        return;
    }
    current_weapon.damage = 25;
    current_weapon.range = 8.0;
    current_weapon.ammo = 30;
    current_weapon.max_ammo = 30;
    current_weapon.fire_rate = 0.2;
    current_weapon.is_firing = false;
    current_weapon.current_frame = 0;
    current_weapon.total_frames = 3;
}

void shoot_weapon(void)
{
    uint32_t current_time = SDL_GetTicks();
    double time_since_last_shot = (current_time - current_weapon.last_shot_time)
        / 1000.0;

    if (time_since_last_shot >= current_weapon.fire_rate
        && current_weapon.ammo > 0) {
        play_shoot_sound();
        current_weapon.is_firing = true;
        current_weapon.last_shot_time = current_time;
        current_weapon.ammo--;
        current_weapon.current_frame = 0;
        double dir_x = cos(player.angle * M_PI / 180.0);
        double dir_y = sin(player.angle * M_PI / 180.0);

        check_enemy_hits(player.x, player.y, dir_x, dir_y,
            current_weapon.range, current_weapon.damage);
    }
}

void update_weapon(void)
{
    static uint32_t last_update_time = 0;
    uint32_t current_time = SDL_GetTicks();
    float delta_time = (current_time - last_update_time) / 1000.0f;

    if (current_weapon.is_firing && delta_time >= 0.05) {
        current_weapon.current_frame++;
        if (current_weapon.current_frame >= current_weapon.total_frames) {
            current_weapon.current_frame = 0;
            current_weapon.is_firing = false;
        }
        last_update_time = current_time;
    } else if (!current_weapon.is_firing) {
        current_weapon.current_frame = 0;
    }
}

void draw_weapon(SDL_Renderer *renderer)
{
    SDL_Rect weapon_rect = {
        SCREEN_WIDTH / 2 - 200,
        SCREEN_HEIGHT - 400,
        400,
        400
    };
    SDL_Rect src_rect = {
        current_weapon.current_frame * 256,
        0,
        256,
        256
    };

    if (!current_weapon.weapon_texture) {
        printf("No weapon texture loaded!\n");
        return;
    }
    if (SDL_RenderCopy(renderer, current_weapon.weapon_texture,
        &src_rect, &weapon_rect) != 0)
        printf("Failed to render weapon: %s\n", SDL_GetError());
}

void cleanup_weapon(void)
{
    if (current_weapon.weapon_texture) {
        SDL_DestroyTexture(current_weapon.weapon_texture);
        current_weapon.weapon_texture = NULL;
    }
}
