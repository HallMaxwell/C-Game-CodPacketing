//
// Created by 2567499168 on 2022-12-7.
//

#include "Fireball.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "Resource.h"

Fireball *Fireball_Create(int y)
{
    Fireball *p = malloc(sizeof(Fireball));
    p->POS.x = 220;
    p->POS.y = y + 20;
    p->POS.w = 50;
    p->POS.h = 50;
    return p;
}

void Fireball_Update(Fireball *self)
{
    self->POS.x += 30;
    if(self->POS.x>2100||self->POS.y<0) free(self);
}

bool Fireball_Hit(Fireball *self, SDL_Rect *rect)
{
    if(self==NULL||rect==NULL) return false;
    if(self->POS.x<rect->x+rect->w&&self->POS.x+self->POS.w>rect->x)
        if(self->POS.y<rect->y+rect->h&&self->POS.y+self->POS.h>rect->y){
            return true;
        }
    return false;
}

void FireballDisplay(SDL_Renderer *renderer, Fireball *self)
{
    if (self == NULL)
        return;
    Fireball_Update(self);
    SDL_RenderCopy(renderer, Get_Obstacle_Text(10), NULL, &(self->POS));
}

void Fireball_Destory(Fireball *self){
    free(self);
}