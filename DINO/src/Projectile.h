#ifndef DINO_CLION_PROJECTILE_H
#define DINO_CLION_PROJECTILE_H

#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Resource.h"

typedef struct{
    SDL_Texture *Text;
    SDL_Rect POS;
    SDL_Rect Frame;
    SDL_Rect Collision_Box;
    int SpeedX,SpeedY;
    int SpeedRotate;
    double Angle;
    int Health;
    bool Animated;
    bool Energy;
}Projectiles;

Projectiles* Projetile_Create(SDL_Texture *Text,SDL_Rect POS,SDL_Rect Frame,SDL_Rect Collision_Box,int SpeedX, int SpeedY, int SpeedRotate, int Health);
void Projectile_HitDino(Projectiles *self);
void Projectile_Quit(Projectiles *self);
void Projectile_Update(Projectiles *self);
void Projectile_Display(SDL_Renderer *Renderer,Projectiles *self,int Speed);
void Projectile_Destroy(Projectiles *self);

//障碍物组件
Projectiles *Projectile_Summon(SDL_Renderer *Renderer, int index, int x, int y, int Set_Speed);

#endif //DINO_CLION_PROJECTILE_H
