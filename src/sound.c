/*
** EPITECH PROJECT, 2025
** MyDream
** File description:
** Sound system implementation
*/

#include "sound.h"
#include <stdio.h>

sound_system_t sound_system = {NULL, NULL};

bool init_sound_system(void)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer initialization failed: %s\n", Mix_GetError());
        return false;
    }

    sound_system.background_music = Mix_LoadMUS("assets/sounds/doom.mp3");
    sound_system.shoot_sound = Mix_LoadWAV("assets/sounds/gun.mp3");

    if (!sound_system.background_music || !sound_system.shoot_sound) {
        printf("Failed to load sounds: %s\n", Mix_GetError());
        cleanup_sound_system();
        return false;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(sound_system.background_music, -1);
    return true;
}

void play_shoot_sound(void)
{
    if (sound_system.shoot_sound)
        Mix_PlayChannel(-1, sound_system.shoot_sound, 0);
}

void cleanup_sound_system(void)
{
    if (sound_system.shoot_sound) {
        Mix_FreeChunk(sound_system.shoot_sound);
        sound_system.shoot_sound = NULL;
    }
    if (sound_system.background_music) {
        Mix_FreeMusic(sound_system.background_music);
        sound_system.background_music = NULL;
    }
    Mix_CloseAudio();
}
