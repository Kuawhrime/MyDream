/*
** KORO PROJECT, 2024
** MyDream
** File description:
** Ray casting engine
*/
 
#include "ray.h"

static void init_wall_params(wall_params_t *params, ray_t *ray, game_state_t *game)
{
    params->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
    params->draw_start = -params->line_height / 2 + SCREEN_HEIGHT / 2 + game->player.pitch;
    params->draw_end = params->line_height / 2 + SCREEN_HEIGHT / 2 + game->player.pitch;
}

static void clamp_wall_params(wall_params_t *params)
{
    if (params->draw_start < 0)
        params->draw_start = 0;
    if (params->draw_end >= SCREEN_HEIGHT)
        params->draw_end = SCREEN_HEIGHT - 1;
}

void draw_wall_line(game_state_t *game, ray_t *ray, int x)
{
    wall_params_t params;

    init_wall_params(&params, ray, game);
    clamp_wall_params(&params);

    SDL_SetRenderDrawColor(game->renderer,
        ray->side == 1 ? 112 : 200,
        ray->side == 1 ? 128 : 200,
        ray->side == 1 ? 144 : 200,
        255);

    SDL_RenderDrawLine(game->renderer,
        x, params.draw_start,
        x, params.draw_end);
}
 
static void init_ray(ray_t *ray, game_state_t *game, double camera_x)
{
    ray->dir_x = game->player.dir.x + game->player.plane.x * camera_x;
    ray->dir_y = game->player.dir.y + game->player.plane.y * camera_x;
    ray->map_x = (int)game->player.pos.x;
    ray->map_y = (int)game->player.pos.y;
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
}
 
static void calculate_step_and_side_dist(ray_t *ray, game_state_t *game)
{
    ray->step_x = (ray->dir_x < 0) ? -1 : 1;
    ray->step_y = (ray->dir_y < 0) ? -1 : 1;
 
    ray->side_dist_x = (ray->dir_x < 0) ?
        (game->player.pos.x - ray->map_x) * ray->delta_dist_x :
        (ray->map_x + 1.0 - game->player.pos.x) * ray->delta_dist_x;
    ray->side_dist_y = (ray->dir_y < 0) ?
        (game->player.pos.y - ray->map_y) * ray->delta_dist_y :
        (ray->map_y + 1.0 - game->player.pos.y) * ray->delta_dist_y;
}
 
static void perform_dda(ray_t *ray, game_state_t *game)
{
    bool hit = false;
 
    while (!hit) {
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (game->map[ray->map_x][ray->map_y])
            hit = true;
    }
}
 
static double calculate_perp_wall_dist(ray_t *ray, game_state_t *game)
{
    if (ray->side == 0)
        return (ray->map_x - game->player.pos.x + (1 - ray->step_x) / 2)
            / ray->dir_x;
    return (ray->map_y - game->player.pos.y + (1 - ray->step_y) / 2)
        / ray->dir_y;
}
 
void cast_rays(game_state_t *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        ray_t ray;
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

        init_ray(&ray, game, camera_x);
        calculate_step_and_side_dist(&ray, game);
        perform_dda(&ray, game);
        ray.perp_wall_dist = calculate_perp_wall_dist(&ray, game);
        draw_wall_line(game, &ray, x);

        if (game->debug_mode && (x % 8 == 0)) {
            draw_debug_ray(game, &ray);
        }
    }

    if (game->debug_mode) {
        render_debug_info(game);
    }

    SDL_RenderPresent(game->renderer);
}
