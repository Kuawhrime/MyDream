/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Enemy management header
*/

#ifndef ENEMY_H_
    #define ENEMY_H_

    #include <SDL2/SDL.h>
    #include <stdbool.h>

    #define MAX_ENEMIES 100
    #define ENEMY_TYPES 3

typedef enum {
    ENEMY_NORMAL,
    ENEMY_FAST,
    ENEMY_TOUGH
} enemy_type_t;

typedef struct {
    double x;
    double y;
    double angle;
    bool is_alive;
    int health;
    double speed;
    SDL_Color color;
    enemy_type_t type;
    uint32_t last_move_time;
} enemy_t;

extern enemy_t enemies[MAX_ENEMIES];
extern SDL_Texture *enemy_textures[ENEMY_TYPES];
extern int enemy_count;

void init_enemies(void);
void spawn_enemy(double x, double y, enemy_type_t type);
void spawn_enemy_wave(int count);
void update_enemies(void);
void render_enemies(void);
void draw_enemies(void);
void check_enemy_hits(double start_x, double start_y, double dir_x,
    double dir_y, double range, int damage);

bool check_enemy_visibility(int enemy_idx);
void draw_enemy_sprite(int enemy_idx, double angle, double distance);

#endif /* !ENEMY_H_ */
