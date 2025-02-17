/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Game engine header
*/

#ifndef ENGINE_H_
    #define ENGINE_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <stdbool.h>
    #include <math.h>

    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define FOV 90.0
    #define MAX_RAY_DEPTH 20.0
    #define RAY_STEP 0.1
    #define NUM_TEXTURES 3
    #define TEX_SIZE 64

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *wall_textures[NUM_TEXTURES];
extern bool show_map;
extern bool game_paused;
extern double last_ray_x;
extern double last_ray_y;

bool init_sdl(void);
void close_sdl(void);
void cast_rays(void);
bool load_textures(void);
void draw_crosshair(SDL_Renderer *renderer);
void cleanup_textures(void);

#endif /* !ENGINE_H_ */
