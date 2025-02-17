/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Player management header
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <SDL2/SDL.h>
    #include <stdbool.h>
    #include <math.h>

typedef struct {
    double x;
    double y;
    double angle;
} player_t;

extern player_t player;

void handle_input(void);
void move_player(double delta_x, double delta_y);
bool is_valid_position(double x, double y);

#endif /* !PLAYER_H_ */