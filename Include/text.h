/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Text rendering system header
*/

#ifndef TEXT_H_
    #define TEXT_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>

bool init_text_system(void);
void render_text(SDL_Renderer *renderer, const char *text,
    int x, int y, SDL_Color color);
void cleanup_text_system(void);

#endif /* !TEXT_H_ */
