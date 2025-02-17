/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Main program entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "player.h"
#include "map_editor.h"
#include "weapon.h"
#include "enemy.h"
#include "menu.h"
#include "text.h"
#include "map.h"
#include "sound.h"

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

static const char USAGE[] = "USAGE\n\t./mydream map_file\n\nDESCRIPTION\n\t"
    "map_file\tPath to the map file to load\n";

static bool initialize_game(const char *map_path)
{
    SDL_ShowCursor(SDL_DISABLE);
    if (!init_sdl()) {
        fprintf(stderr, "IS NOT WORKING,  SDL\n");
        return false;
    }
    if (!init_text_system()) {
        fprintf(stderr, "IS NOT WORKING,  text system\n");
        close_sdl();
        return false;
    }
    if (!load_map_from_file(map_path)) {
        fprintf(stderr, "Error: Invalid map file: %s\n", map_path);
        close_sdl();
        return false;
    }
    if (!init_sound_system()) {
        fprintf(stderr, "IS NOT WORKING,  sound system\n");
        close_sdl();
        return false;
    }
    SDL_ShowCursor(SDL_DISABLE);
    init_menu();
    init_weapon();
    init_enemies();
    return true;
}

static void handle_events(bool *running)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        toggle_menu();
                        break;
                    case SDLK_SPACE:
                        if (!game_paused)
                            shoot_weapon();
                        break;
                }
                break;
        }
        if (game_paused)
            handle_menu_events(&event, running);
    }
    if (!game_paused)
        handle_input();
}

static void update_game(void)
{
    if (game_paused)
        return;
    update_weapon();
    update_enemies();
}

static void render_game(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &floor);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_Rect ceiling = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &ceiling);

    cast_rays();
    render_enemies();

    if (show_map) {
        draw_map_editor();
        draw_enemies();
    }
    draw_weapon(renderer);
    draw_crosshair(renderer);
    render_menu(renderer);
    SDL_RenderPresent(renderer);
}

static void cleanup_game(void)
{
    cleanup_weapon();
    cleanup_text_system();
    close_sdl();
}

int main(int argc, char *argv[])
{
    bool running = true;
    uint32_t frame_start;
    int frame_time;

    if (argc != 2) {
        printf("%s", USAGE);
        return 84;
    }

    srand(time(NULL));
    if (!initialize_game(argv[1])) {
        return 84;
    }
    while (running) {
        frame_start = SDL_GetTicks();
        handle_events(&running);
        update_game();
        render_game();
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frame_time);
    }
    cleanup_game();
    return 0;
}
