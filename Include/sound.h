/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Sound system header
*/

#ifndef SOUND_H_
    #define SOUND_H_

    #include <SDL2/SDL_mixer.h>
    #include <stdbool.h>

typedef struct {
    Mix_Music *background_music;
    Mix_Chunk *shoot_sound;
} sound_system_t;

extern sound_system_t sound_system;

bool init_sound_system(void);
void play_shoot_sound(void);
void cleanup_sound_system(void);

#endif /* !SOUND_H_ */
