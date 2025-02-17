/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Game menu header
*/

#ifndef MENU_H_
    #define MENU_H_

    #include <SDL2/SDL.h>
    #include <stdbool.h>

typedef enum {
    MENU_RESUME,
    MENU_SETTINGS,
    MENU_RESTART,
    MENU_QUIT,
    MENU_ITEMS_COUNT
} menu_option_t;

typedef struct {
    bool is_visible;
    menu_option_t selected_option;
    float mouse_sensitivity;
    bool in_settings;
} menu_state_t;

void init_menu(void);
void toggle_menu(void);
void handle_menu_events(SDL_Event *event, bool *game_running);
void render_menu(SDL_Renderer *renderer);
void update_mouse_sensitivity(float new_value);
float get_mouse_sensitivity(void);

#endif /* !MENU_H_ */
