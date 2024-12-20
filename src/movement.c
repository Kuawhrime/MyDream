/*
** KORO PROJECT, 2024
** MyDream
** File description:
** movement
*/

#include "ray.h"

void handle_mouse(game_state_t *game)
{
    int x, y;
    double rot_speed;
    double old_dir_x;
    double old_plane_x;

    if (!game->window_focused)
        return;

    //? Handle mouse button to toggle mouse control
    uint32_t mouse_state = SDL_GetMouseState(NULL, NULL);
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (!game->mouse_active) {
            game->mouse_active = true;
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }

    if (!game->mouse_active)
        return;

    SDL_GetRelativeMouseState(&x, &y);
    rot_speed = x * MOUSE_SENSITIVITY;

    //? Horizontal mouse movement (looking left/right)
    old_dir_x = game->player.dir.x;
    game->player.dir.x = game->player.dir.x * cos(rot_speed)
        - game->player.dir.y * sin(rot_speed);
    game->player.dir.y = old_dir_x * sin(rot_speed)
        + game->player.dir.y * cos(rot_speed);

    old_plane_x = game->player.plane.x;
    game->player.plane.x = game->player.plane.x * cos(rot_speed)
        - game->player.plane.y * sin(rot_speed);
    game->player.plane.y = old_plane_x * sin(rot_speed)
        + game->player.plane.y * cos(rot_speed);

    //? Vertical mouse movement (looking up/down)
    game->player.vertical_angle -= y * VERTICAL_LOOK_SPEED;
    if (game->player.vertical_angle > MAX_VERTICAL_ANGLE)
        game->player.vertical_angle = MAX_VERTICAL_ANGLE;
    if (game->player.vertical_angle < -MAX_VERTICAL_ANGLE)
        game->player.vertical_angle = -MAX_VERTICAL_ANGLE;
    
    game->player.pitch = game->player.vertical_angle;
}

static void move_forward(game_state_t *game)
{
    double new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
    double new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;

    if (!game->map[(int)new_x][(int)game->player.pos.y])
        game->player.pos.x = new_x;
    if (!game->map[(int)game->player.pos.x][(int)new_y])
        game->player.pos.y = new_y;
}

static void move_backward(game_state_t *game)
{
    double new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
    double new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;

    if (!game->map[(int)new_x][(int)game->player.pos.y])
        game->player.pos.x = new_x;
    if (!game->map[(int)game->player.pos.x][(int)new_y])
        game->player.pos.y = new_y;
}

static void move_left(game_state_t *game)
{
    double new_x = game->player.pos.x - game->player.plane.x * MOVE_SPEED;
    double new_y = game->player.pos.y - game->player.plane.y * MOVE_SPEED;

    if (!game->map[(int)new_x][(int)game->player.pos.y])
        game->player.pos.x = new_x;
    if (!game->map[(int)game->player.pos.x][(int)new_y])
        game->player.pos.y = new_y;
}

static void move_right(game_state_t *game)
{
    double new_x = game->player.pos.x + game->player.plane.x * MOVE_SPEED;
    double new_y = game->player.pos.y + game->player.plane.y * MOVE_SPEED;

    if (!game->map[(int)new_x][(int)game->player.pos.y])
        game->player.pos.x = new_x;
    if (!game->map[(int)game->player.pos.x][(int)new_y])
        game->player.pos.y = new_y;
}

void handle_movement(game_state_t *game)
{
    const uint8_t *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W])
        move_forward(game);
    if (state[SDL_SCANCODE_S])
        move_backward(game);
    if (state[SDL_SCANCODE_A])
        move_left(game);
    if (state[SDL_SCANCODE_D])
        move_right(game);
}