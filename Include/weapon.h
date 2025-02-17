/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Weapon system header
*/

#ifndef WEAPON_H_
    #define WEAPON_H_

    #include <SDL2/SDL.h>
    #include <stdbool.h>
    #include <math.h>

typedef struct {
    int damage;
    double range;
    int ammo;
    int max_ammo;
    double last_shot_time;
    double fire_rate;
    SDL_Texture *weapon_texture;
    bool is_firing;
    int current_frame;
    int total_frames;
} weapon_t;

extern weapon_t current_weapon;

void init_weapon(void);
void update_weapon(void);
void shoot_weapon(void);
void draw_weapon(SDL_Renderer *renderer);
void cleanup_weapon(void);

#endif /* !WEAPON_H_ */
