//
// Created by 2567499168 on 2022-12-7.
//

#include "Background.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Background.h"
#include "Resource.h"

SDL_Rect BEGIN_POS = {0, 0, 3200, 800};

Background *Background_Create(int index, int SpeedMultiplier)
{
    Background *b = malloc(sizeof(Background));
    b->Text = Get_Layer_Text(index);
    b->SpeedMultiplier = SpeedMultiplier;
    b->Dest = BEGIN_POS;
    return b;
}

void Update_Background(SDL_Renderer *renderer,Background *self,int speed)
{
    (self->Dest.x)-=speed*(self->SpeedMultiplier);
    if((self->Dest.x)<=-1600) self->Dest.x=0;
    SDL_RenderCopy(renderer,self->Text,NULL,&(self->Dest));
}

void Destroy_Background(Background *self)
{
    free(self);
}