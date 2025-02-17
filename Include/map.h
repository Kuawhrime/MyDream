/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Map system header
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <stdbool.h>

    #define MAP_WIDTH 24
    #define MAP_HEIGHT 24
    #define TILE_SIZE 32
    #define ZEROANDN +2

extern int map[MAP_WIDTH][MAP_HEIGHT];

bool load_map_from_file(const char *filepath);

#endif /* !MAP_H_ */
