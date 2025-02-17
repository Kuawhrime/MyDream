/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Map loading system implementation
*/

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[MAP_WIDTH][MAP_HEIGHT] = {{0}};

static void init_empty_map(void)
{
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (i == 0 || i == MAP_WIDTH - 1 || j == 0 || j == MAP_HEIGHT - 1)
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }
}

bool load_map_from_file(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char line[MAP_WIDTH + ZEROANDN];
    int y = 0;

    if (!file) {
        printf("Error: Your file is weird map file: %s\n", filepath);
        init_empty_map();
        return false;
    }

    while (fgets(line, sizeof(line), file) && y < MAP_HEIGHT) {
        int len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        
        for (int x = 0; x < MAP_WIDTH && x < len; x++) {
            switch (line[x]) {
                case '0':
                    map[x][y] = 0;
                    break;
                case '1':
                    map[x][y] = 1;
                    break;
                case '2':
                    map[x][y] = 2;
                    break;
                case '3':
                    map[x][y] = 3;
                    break;
                default:
                    map[x][y] = 0;
            }
        }
        y++;
    }

    for (int i = 0; i < MAP_WIDTH; i++) {
        if (map[i][0] == 0 || map[i][MAP_HEIGHT - 1] == 0) {
            printf("Error: Map must have walls on top and bottom borders\n");
            init_empty_map();
            fclose(file);
            return false;
        }
    }
    for (int j = 0; j < MAP_HEIGHT; j++) {
        if (map[0][j] == 0 || map[MAP_WIDTH - 1][j] == 0) {
            printf("Error: Map must have walls on left and right borders\n");
            init_empty_map();
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}
