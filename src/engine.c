/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Game engine implementation
*/

#include "engine.h"
#include "player.h"
#include "map.h"
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *wall_textures[NUM_TEXTURES] = {NULL};
bool show_map = false;
double last_ray_x = 0;
double last_ray_y = 0;
bool game_paused = false;

bool load_textures(void)
{
    const char *texture_files[NUM_TEXTURES] = {
        "assets/textures/Brick/Brick_02-128x128.png",
        "assets/textures/Stone/Stone_01-128x128.png",
        "assets/textures/Metal/Metal_08-128x128.png"
    };

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        return false;
    }
    for (int i = 0; i < NUM_TEXTURES; i++) {
        SDL_Surface *surface = IMG_Load(texture_files[i]);
        if (!surface) {
            printf("Failed to load texture %s: %s\n",
                texture_files[i], IMG_GetError());
            return false;
        }
        wall_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!wall_textures[i]) {
            printf("Failed to create texture: %s\n", SDL_GetError());
            return false;
        }
    }
    return true;
}

void cleanup_textures(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++) {
        if (wall_textures[i]) {
            SDL_DestroyTexture(wall_textures[i]);
            wall_textures[i] = NULL;
        }
    }
    IMG_Quit();
}

bool init_sdl(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("MyDream",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return load_textures();
}

void close_sdl(void)
{
    cleanup_textures();
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_crosshair(SDL_Renderer *renderer)
{
    int center_x = SCREEN_WIDTH / 2;
    int center_y = SCREEN_HEIGHT / 2;
    int size = 10;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, center_x - size, center_y,
        center_x + size, center_y);
    SDL_RenderDrawLine(renderer, center_x, center_y - size,
        center_x, center_y + size);
}
