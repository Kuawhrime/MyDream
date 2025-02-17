/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Menu system implementation
*/

#include "menu.h"
#include "engine.h"
#include "text.h"
#include "game.h"
#include <stdio.h>

static menu_state_t menu_state = {
    .is_visible = false,
    .selected_option = MENU_RESUME,
    .mouse_sensitivity = 0.15f,
    .in_settings = false
};

static SDL_Rect menu_rects[MENU_ITEMS_COUNT];
static const char *menu_texts[MENU_ITEMS_COUNT] = {
    "Resume",
    "Settings",
    "Restart",
    "Quit"
};

// Prototypes des fonctions statiques
static void handle_settings_click(int mouse_x, int mouse_y, bool *game_running);
static void handle_main_menu_click(int mouse_x, int mouse_y, bool *game_running);
static bool is_point_in_rect(int x, int y, SDL_Rect *rect);
static void render_settings_menu(SDL_Renderer *renderer, SDL_Color text_color);
static void render_main_menu(SDL_Renderer *renderer, SDL_Color text_color,
    SDL_Color hover_text_color);

static bool is_point_in_rect(int x, int y, SDL_Rect *rect)
{
    return x >= rect->x && x < rect->x + rect->w &&
           y >= rect->y && y < rect->y + rect->h;
}

static void handle_settings_click(int mouse_x, int mouse_y,
    bool *game_running __attribute__((unused)))
{
    if (mouse_y >= SCREEN_HEIGHT / 2 - 50 && mouse_y <= SCREEN_HEIGHT / 2 + 50) {
        float relative_x = (float)(mouse_x - (SCREEN_WIDTH / 2 - 100)) / 200.0f;
        if (relative_x >= 0 && relative_x <= 1)
            menu_state.mouse_sensitivity = 0.05f + relative_x * 0.25f;
    }
    SDL_Rect back_button = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 40};
    if (is_point_in_rect(mouse_x, mouse_y, &back_button))
        menu_state.in_settings = false;
}

static void handle_main_menu_click(int mouse_x, int mouse_y, bool *game_running)
{
    for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
        if (is_point_in_rect(mouse_x, mouse_y, &menu_rects[i])) {
            switch (i) {
                case MENU_RESUME:
                    toggle_menu();
                    break;
                case MENU_SETTINGS:
                    menu_state.in_settings = true;
                    break;
                case MENU_RESTART:
                    restart_game();
                    toggle_menu();
                    break;
                case MENU_QUIT:
                    *game_running = false;
                    break;
            }
            break;
        }
    }
}

static void render_settings_menu(SDL_Renderer *renderer, SDL_Color text_color)
{
    render_text(renderer, "Mouse Sensitivity", SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 - 50, text_color);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect slider = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, 200, 20};
    SDL_RenderFillRect(renderer, &slider);

    float handle_pos = (menu_state.mouse_sensitivity - 0.05f) / 0.25f;
    SDL_Rect handle = {
        SCREEN_WIDTH / 2 - 100 + (int)(handle_pos * 200) - 5,
        SCREEN_HEIGHT / 2 - 15,
        10,
        30
    };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &handle);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect back_button = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 40};
    SDL_RenderFillRect(renderer, &back_button);
    render_text(renderer, "Back", SCREEN_WIDTH / 2 - 20,
        SCREEN_HEIGHT - 95, text_color);
}

static void render_main_menu(SDL_Renderer *renderer, SDL_Color text_color,
    SDL_Color hover_text_color)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
        bool is_hovered = is_point_in_rect(mouse_x, mouse_y, &menu_rects[i]);
        SDL_SetRenderDrawColor(renderer, is_hovered ? 100 : 50,
            is_hovered ? 100 : 50, is_hovered ? 100 : 50, 255);
        SDL_RenderFillRect(renderer, &menu_rects[i]);

        int text_width = strlen(menu_texts[i]) * 15;
        int text_x = menu_rects[i].x + (menu_rects[i].w - text_width) / 2;
        int text_y = menu_rects[i].y + (menu_rects[i].h - 24) / 2;

        render_text(renderer, menu_texts[i], text_x, text_y,
            is_hovered ? hover_text_color : text_color);
    }
}

void handle_menu_events(SDL_Event *event, bool *game_running)
{
    if (!menu_state.is_visible || !event)
        return;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
        if (menu_state.in_settings) {
            handle_settings_click(mouse_x, mouse_y, game_running);
        } else {
            handle_main_menu_click(mouse_x, mouse_y, game_running);
        }
    }
}

void render_menu(SDL_Renderer *renderer)
{
    if (!menu_state.is_visible)
        return;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_Rect fullscreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &fullscreen);

    SDL_Color text_color = {255, 255, 255, 255};
    SDL_Color hover_text_color = {255, 255, 0, 255};

    if (menu_state.in_settings) {
        render_settings_menu(renderer, text_color);
    } else {
        render_main_menu(renderer, text_color, hover_text_color);
    }
}

float get_mouse_sensitivity(void)
{
    return menu_state.mouse_sensitivity;
}

void init_menu(void)
{
    int start_y = SCREEN_HEIGHT / 3;
    int item_height = 50;
    int item_width = 200;

    for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
        menu_rects[i] = (SDL_Rect){
            SCREEN_WIDTH / 2 - item_width / 2,
            start_y + i * (item_height + 10),
            item_width,
            item_height
        };
    }
}

void toggle_menu(void)
{
    menu_state.is_visible = !menu_state.is_visible;
    menu_state.in_settings = false;
    game_paused = menu_state.is_visible;

    if (menu_state.is_visible) {
        SDL_ShowCursor(SDL_ENABLE);
        SDL_SetRelativeMouseMode(SDL_FALSE);
    } else {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

void update_mouse_sensitivity(float new_value)
{
    menu_state.mouse_sensitivity = new_value;
}
