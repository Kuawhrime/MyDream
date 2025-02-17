/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Text rendering system implementation
*/

#include "text.h"
#include <stdio.h>

static TTF_Font *game_font = NULL;

bool init_text_system(void)
{
    if (TTF_Init() < 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        return false;
    }
    game_font = TTF_OpenFont("assets/fonts/OpenSans-Bold.ttf", 24);
    if (!game_font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void render_text(SDL_Renderer *renderer, const char *text,
    int x, int y, SDL_Color color)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest = {x, y, 0, 0};

    if (!game_font || !text)
        return;
    surface = TTF_RenderText_Solid(game_font, text, color);
    if (!surface) {
        printf("Failed to render text surface: %s\n", TTF_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Failed to create texture from rendered text: %s\n",
            SDL_GetError());
        return;
    }
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}

void cleanup_text_system(void)
{
    if (game_font) {
        TTF_CloseFont(game_font);
        game_font = NULL;
    }
    TTF_Quit();
}
