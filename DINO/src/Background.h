//
// Created by 2567499168 on 2022-12-7.
//

#ifndef DINO_CLION_BACKGROUND_H
#define DINO_CLION_BACKGROUND_H

#include<SDL2/SDL.h>

typedef struct {
    SDL_Rect Dest;
    int SpeedMultiplier;
    SDL_Texture *Text;
}Background;

Background *Background_Create(int index, int SpeedMultiplier);
void Update_Background(SDL_Renderer *renderer,Background *self,int speed);
void Destroy_Background(Background *self);

#endif //DINO_CLION_BACKGROUND_H
