//
// Created by 2567499168 on 2022-12-7.
//

#include "Projectile.h"

#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "Resource.h"
#include "Dino.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

//障碍物贴图大小
#define Bird_WIDTH 200
#define Bird_HEIGHT 150
#define Cactus_BIG_WIDTH 100
#define Cactus_BIG_HEIGHT 200
#define Cactus_MIX_WIDTH 300
#define Cactus_MIX_HEIGHT 200
#define Cactus_SMALL_WIDTH 60
#define Cactus_SMALL_HEIGHT 120

int birdtime=0;

Projectiles *Projetile_Create(SDL_Texture *Text, SDL_Rect POS, SDL_Rect Frame, SDL_Rect Collision_Box, int SpeedX, int SpeedY, int SpeedRotate, int Health)
{
    Projectiles *p = malloc(sizeof(Projectiles));
    p->Text = Text;
    p->POS = POS;
    p->Frame = Frame;
    p->Collision_Box = Collision_Box;
    p->SpeedX = SpeedX;
    p->SpeedY = SpeedY;
    p->SpeedRotate = SpeedRotate;
    p->Angle = 0;
    p->Health = Health;
    p->Animated = false;
    p->Energy=false;
    return p;
}

void Projectile_HitDino(Projectiles *self){
    SDL_Rect temp=Dino_Get_Collision();
    if(self->Collision_Box.x<temp.x+temp.w){
        if(self->Collision_Box.x+self->Collision_Box.w>temp.x){
            if(self->Collision_Box.y<temp.y+temp.h){
                if(self->Collision_Box.y+self->Collision_Box.h>temp.y){
                    Dino_Hit(self->Energy);
                    if(self->Energy){
                        self->POS.x=-1000;
                    }
                }
            }
        }
    }
}

void Projectile_Quit(Projectiles *self){
    self->POS.y=-1000;
}

void Projectile_Update(Projectiles *self)
{
    //更新运动状态
    self->POS.x -= self->SpeedX;
    self->POS.y -= self->SpeedY;
    self->Collision_Box= self->POS;
    self->Angle += self->SpeedRotate;
    if (self->Angle > 360)
        self->Angle -= 360;
    if (self->Angle < -360)
        self->Angle += 360;
    //更新动画
    if (self->Animated)
    {
        birdtime++;
        if(birdtime>15){
            if(birdtime>30){
                birdtime=0;
            }
            else{
                self->Text=Get_Obstacle_Text(2);
            }
        }
        else self->Text= Get_Obstacle_Text(1);
    }
}

void Projectile_Display(SDL_Renderer *Renderer, Projectiles *self,int Speed)
{
    if (self == NULL)
        return;
    self->SpeedX=Speed*8;
    Projectile_Update(self);
    Projectile_HitDino(self);
    if (self->Animated == true)
        SDL_RenderCopyEx(Renderer, self->Text, &(self->Frame), &(self->POS), self->Angle, NULL, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(Renderer, self->Text, NULL, &(self->POS), self->Angle, NULL, SDL_FLIP_NONE);
}

Projectiles *Projectile_Summon(SDL_Renderer *Renderer, int index, int x, int y, int Set_Speed)
{
    SDL_Rect POS, Frame, Collision_Box;
    POS.x = x;
    POS.y=y;
    Collision_Box.x = POS.x;
    Collision_Box.y = POS.y;
    Frame.x = 0;
    Frame.y = 0;
    if (index == 1 || index == 2) // Bird
    {
        POS.y = rand() % 250 + 200;
        POS.w = Bird_WIDTH;
        POS.h = Bird_HEIGHT;
        Frame.w = Bird_WIDTH;
        Frame.h = Bird_HEIGHT;
        Collision_Box.x += 40;
        Collision_Box.y += 45;
        Collision_Box.w = 120;
        Collision_Box.h = 60;
        Projectiles *temp = Projetile_Create(Get_Obstacle_Text(1), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
        temp->Animated = true;
        return temp;
    }
    if (index == 3)// Cactus_BIG1
    {
        POS.y=500;
        POS.w = Cactus_BIG_WIDTH;
        POS.h = Cactus_BIG_HEIGHT;
        Frame.w = Cactus_BIG_WIDTH;
        Frame.h = Cactus_BIG_HEIGHT;
        Collision_Box.w = Cactus_BIG_WIDTH;
        Collision_Box.h = Cactus_BIG_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if(index==4)//Cactus_BIG2
    {
        POS.y=500;
        POS.w = Cactus_BIG_WIDTH*2;
        POS.h = Cactus_BIG_HEIGHT;
        Frame.w = Cactus_BIG_WIDTH*2;
        Frame.h = Cactus_BIG_HEIGHT;
        Collision_Box.w = Cactus_BIG_WIDTH*2;
        Collision_Box.h = Cactus_BIG_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if(index==5)//Cactus_MIX
    {
        POS.y=500;
        POS.w = Cactus_MIX_WIDTH;
        POS.h = Cactus_MIX_HEIGHT;
        Frame.w = Cactus_MIX_WIDTH;
        Frame.h = Cactus_MIX_HEIGHT;
        Collision_Box.w = Cactus_MIX_WIDTH;
        Collision_Box.h = Cactus_MIX_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if(index==6)//Cactus_SMALL1
    {
        POS.y=580;
        POS.w = Cactus_SMALL_WIDTH;
        POS.h = Cactus_SMALL_HEIGHT;
        Frame.w = Cactus_SMALL_WIDTH;
        Frame.h = Cactus_SMALL_HEIGHT;
        Collision_Box.w = Cactus_SMALL_HEIGHT;
        Collision_Box.h = Cactus_SMALL_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if(index==7)//Cactus_SMALL2
    {
        POS.y=580;
        POS.w = Cactus_SMALL_WIDTH*2;
        POS.h = Cactus_SMALL_HEIGHT;
        Frame.w = Cactus_SMALL_WIDTH*2;
        Frame.h = Cactus_SMALL_HEIGHT;
        Collision_Box.w = Cactus_SMALL_WIDTH*2;
        Collision_Box.h = Cactus_SMALL_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if(index==8)//Cactus_SMALL3
    {
        POS.y=580;
        POS.w = Cactus_SMALL_WIDTH*3;
        POS.h = Cactus_SMALL_HEIGHT;
        Frame.w = Cactus_SMALL_WIDTH*3;
        Frame.h = Cactus_SMALL_HEIGHT;
        Collision_Box.w = Cactus_SMALL_WIDTH*3;
        Collision_Box.h = Cactus_SMALL_HEIGHT;
        return Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
    }
    if (index == 9) // Energy
    {
        POS.y = rand() % 300 + 150;
        POS.w = 50;
        POS.h = 50;
        Frame.w = 50;
        Frame.h = 50;
        Collision_Box.x += 10;
        Collision_Box.y += 10;
        Collision_Box.w = 30;
        Collision_Box.h = 30;
        Projectiles *temp = Projetile_Create(Get_Obstacle_Text(index), POS, Frame, Collision_Box, Set_Speed * 8, 0, 0, 1);
        temp->Energy=true;
        return temp;
    }
    return NULL;
}

void Projectile_Destroy(Projectiles *self)
{
    free(self);
    self=NULL;
}
