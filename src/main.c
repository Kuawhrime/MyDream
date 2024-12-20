/*
** KORO PROJECT, 2024
** MyDream
** File description:
** Main
*/

#include "ray.h"

static void init_player(player_t *player)
{
    player->pos.x = 2;
    player->pos.y = 2;
    player->dir.x = 1;
    player->dir.y = 0;
    player->plane.x = 0;
    player->plane.y = 0.66;
    player->vertical_angle = 0;
    player->pitch = 0;
}

int main(void)
{
    game_state_t game = {0};
    SDL_Event event;

    init_player(&game.player);
    if (!init_sdl(&game))
        return 84;

    game.running = true;
    while (game.running) {
        //TODO handle event function
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    game.running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            game.running = false;
                            break;
                        case SDLK_TAB:
                            game.debug_mode = !game.debug_mode;
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    handle_window_event(&game, &event);
                    break;
            }
        }
        handle_movement(&game);
        handle_mouse(&game);
        cast_rays(&game);
    }
    cleanup_sdl(&game);
    return 0;
}

