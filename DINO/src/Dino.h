//
// Created by 2567499168 on 2022-12-7.
//

#ifndef DINO_CLION_DINO_H
#define DINO_CLION_DINO_H

#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Resource.h"


typedef struct{
    bool IsSprint;
    bool InAir;
    bool Failed;
    bool After_Hit;
    bool God_Mode;
    int Velocity;
    SDL_Rect Pos;
    SDL_Rect Collision_Box;
}Dino;

void Dino_Init();
bool Dino_SpeedUp();
int Dino_Get_Mouth();
int Dino_Get_Stamia();
void Dino_Use_Stamia();
SDL_Rect Dino_Get_Collision();
int Dino_Getalpha();
void Dino_Hit(bool energy);
bool Dino_Alive();
void Dino_Jump();
void Dino_Sprint();
void Dino_DeSprint();
void Dino_GodMode(bool isPress);
void Dino_Update_POS();
SDL_Texture *Current_Motion();
void Dino_Display(SDL_Renderer *renderer);

void UI_Display(SDL_Renderer *renderer);

#endif //DINO_CLION_DINO_H
