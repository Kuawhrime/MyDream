/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Game state management
*/

#include "game.h"
#include "player.h"
#include "enemy.h"
#include "weapon.h"

void restart_game(void)
{
    player.x = 4;
    player.y = 4;
    player.angle = 0;

    current_weapon.ammo = current_weapon.max_ammo;
    current_weapon.is_firing = false;
    current_weapon.current_frame = 0;

    for (int i = 0; i < enemy_count; i++) {
        enemies[i].is_alive = false;
    }
    enemy_count = 0;
    init_enemies();
}
