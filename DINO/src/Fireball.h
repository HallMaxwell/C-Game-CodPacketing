//
// Created by 2567499168 on 2022-12-7.
//

#ifndef DINO_CLION_FIREBALL_H
#define DINO_CLION_FIREBALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    SDL_Rect POS;
}Fireball;

Fireball *Fireball_Create(int y);
void Fireball_Update(Fireball *self);
bool Fireball_Hit(Fireball *self, SDL_Rect *rect);
void FireballDisplay(SDL_Renderer *renderer,Fireball *self);
void Fireball_Destory(Fireball *self);

#endif //DINO_CLION_FIREBALL_H
