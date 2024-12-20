/*
** KORO PROJECT, 2024
** MyDream
** File description:
** Ray casting engine header
*/

#ifndef RAY_H_
    #define RAY_H_

    #include <SDL2/SDL.h>
    #include <stdbool.h>
    #include <math.h>

    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define MAP_WIDTH 24
    #define MAP_HEIGHT 24
    #define MOVE_SPEED 0.03
    #define MOUSE_SENSITIVITY 0.001
    #define VERTICAL_LOOK_SPEED 0.8
    #define MAX_VERTICAL_ANGLE (SCREEN_HEIGHT / 2)

    typedef struct position_s {
        double x;
        double y;
    } position_t;

    typedef struct player_s {
        position_t pos;
        position_t dir;
        position_t plane;
        double vertical_angle;
        double pitch;
    } player_t;

    typedef struct game_state_s {
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool running;
        bool window_focused;
        bool mouse_active;
        bool debug_mode;
        player_t player;
        const uint8_t (*map)[MAP_WIDTH];
    } game_state_t;

    typedef struct ray_s {
        double dir_x;
        double dir_y;
        double delta_dist_x;
        double delta_dist_y;
        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;
        int map_x;
        int map_y;
        int side;
        double perp_wall_dist;
    } ray_t;

    typedef struct wall_params_s {
        int draw_start;
        int draw_end;
        int line_height;
        int color;
    } wall_params_t;

    typedef void (*input_handler_t)(game_state_t *);

    // Core initialization functions
    bool init_sdl(game_state_t *game);
    void cleanup_sdl(game_state_t *game);

    // Game loop functions
    void handle_movement(game_state_t *game);
    void handle_mouse(game_state_t *game);
    void handle_window_event(game_state_t *game, SDL_Event *event);
    void cast_rays(game_state_t *game);

    //debug function
    void draw_debug_ray(game_state_t *game, ray_t *ray);
    void draw_debug_player(game_state_t *game);
    void render_debug_info(game_state_t *game);
    void draw_wall_line(game_state_t *game, ray_t *ray, int x);


#endif /* !RAY_H_ */
