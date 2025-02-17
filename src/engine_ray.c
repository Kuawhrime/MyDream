/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Ray casting implementation
*/

#include "engine.h"
#include "player.h"
#include "map.h"

typedef struct {
    double ray_dir_x;
    double ray_dir_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int map_x;
    int map_y;
    int hit;
    int side;
    int tex_num;
} ray_data_t;

static void draw_wall_line(int x, double perp_wall_dist, int side,
    int tex_num, ray_data_t *ray)
{
    int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    double wall_x;

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    wall_x = (side == 0) ?
        player.y + perp_wall_dist * ray->ray_dir_y :
        player.x + perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    int tex_x = (int)(wall_x * TEX_SIZE);
    if ((side == 0 && ray->ray_dir_x > 0) ||
        (side == 1 && ray->ray_dir_y < 0))
        tex_x = TEX_SIZE - tex_x - 1;
    tex_x = (tex_x < 0) ? 0 : (tex_x >= TEX_SIZE ? TEX_SIZE - 1 : tex_x);
    SDL_Rect src = {tex_x, 0, 1, TEX_SIZE};
    SDL_Rect dst = {x, draw_start, 1, draw_end - draw_start};
    int brightness = side == 1 ? 200 : 255;

    brightness = (int)(brightness * (1.0 - (perp_wall_dist / MAX_RAY_DEPTH)));
    brightness = (brightness < 0) ? 0 : (brightness > 255 ? 255 : brightness);
    if (tex_num >= 0 && tex_num < NUM_TEXTURES && wall_textures[tex_num]) {
        SDL_SetTextureColorMod(wall_textures[tex_num],
            brightness, brightness, brightness);
        SDL_RenderCopy(renderer, wall_textures[tex_num], &src, &dst);
    }
}

static void cast_single_ray(int x, double camera_x)
{
    ray_data_t ray;
    double perp_wall_dist;

    ray.ray_dir_x = cos(player.angle * M_PI / 180.0) -
        sin(player.angle * M_PI / 180.0) * camera_x;
    ray.ray_dir_y = sin(player.angle * M_PI / 180.0) +
        cos(player.angle * M_PI / 180.0) * camera_x;
    ray.map_x = (int)player.x;
    ray.map_y = (int)player.y;
    ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e30 : fabs(1 / ray.ray_dir_x);
    ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e30 : fabs(1 / ray.ray_dir_y);
    ray.step_x = (ray.ray_dir_x < 0) ? -1 : 1;
    ray.step_y = (ray.ray_dir_y < 0) ? -1 : 1;
    ray.hit = 0;
    ray.side = 0;
    ray.tex_num = 0;

    if (ray.ray_dir_x < 0)
        ray.side_dist_x = (player.x - ray.map_x) * ray.delta_dist_x;
    else
        ray.side_dist_x = (ray.map_x + 1.0 - player.x) * ray.delta_dist_x;
    if (ray.ray_dir_y < 0)
        ray.side_dist_y = (player.y - ray.map_y) * ray.delta_dist_y;
    else
        ray.side_dist_y = (ray.map_y + 1.0 - player.y) * ray.delta_dist_y;

    while (ray.hit == 0) {
        if (ray.side_dist_x < ray.side_dist_y) {
            ray.side_dist_x += ray.delta_dist_x;
            ray.map_x += ray.step_x;
            ray.side = 0;
        } else {
            ray.side_dist_y += ray.delta_dist_y;
            ray.map_y += ray.step_y;
            ray.side = 1;
        }
        if (!is_valid_position(ray.map_x, ray.map_y)) {
            ray.hit = 1;
            ray.tex_num = 0;
        } else if (map[ray.map_x][ray.map_y] > 0) {
            ray.hit = 1;
            ray.tex_num = map[ray.map_x][ray.map_y] - 1;
            if (ray.tex_num >= NUM_TEXTURES)
                ray.tex_num = 0;
            last_ray_x = ray.map_x;
            last_ray_y = ray.map_y;
        }
    }

    if (ray.side == 0)
        perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
    else
        perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
    if (perp_wall_dist <= 0)
        perp_wall_dist = 0.1;

    draw_wall_line(x, perp_wall_dist, ray.side, ray.tex_num, &ray);
}

void cast_rays(void)
{
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        cast_single_ray(x, camera_x);
    }
}
