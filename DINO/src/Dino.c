//
// Created by 2567499168 on 2022-12-7.
//

#include "Dino.h"

#include <SDL2/SDL.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

#define GROUND_HEIGHT 500
#define JUMP_VELOCITY 1840
#define FALL_VELOCITY -1840
#define GRAVITY 80

Dino Player;
int health = 3;
int stamia = 3;

int flashtime = 0;

int Godmodtime = 0;

int Motion_Rate = 5;
int Motion_RateCount = 1;

SDL_Rect Heart_Pos;
SDL_Rect Stamia_Pos;

void Dino_Init()
{
    health = 3;
    stamia = 3;
    flashtime = 0;
    Godmodtime = 0;
    Player.Failed = false;
    Player.InAir = false;
    Player.IsSprint = false;
    Player.After_Hit = false;
    Player.God_Mode = false;
    Player.Velocity = 0;
    Player.Pos.x = 20;
    Player.Pos.y = 500;
    Player.Pos.w = 200;
    Player.Pos.h = 200;
    Player.Collision_Box.x = 60;
    Player.Collision_Box.y = 540;
    Player.Collision_Box.w = 100;
    Player.Collision_Box.h = 150;

    Heart_Pos.x = 20;
    Heart_Pos.y = 700;
    Heart_Pos.w = 200;
    Heart_Pos.h = 60;
    Stamia_Pos.x = 270;
    Stamia_Pos.y = 700;
    Stamia_Pos.w = 200;
    Stamia_Pos.h = 60;
}

bool Dino_SpeedUp()
{
    return Player.IsSprint;
}

SDL_Rect Dino_Get_Collision()
{
    return Player.Collision_Box;
}

int Dino_Get_Mouth()
{
    return Player.Collision_Box.y;
}

int Dino_Get_Stamia()
{
    return stamia;
}

void Dino_Use_Stamia()
{
    stamia--;
}

int Dino_Getalpha()
{
    if (Player.God_Mode)
    {
        Godmodtime++;
        if (Godmodtime > 200)
        {
            Godmodtime = 0;
            Player.After_Hit = true;
            Player.God_Mode = false;
        }
        return 100;
    }
    if (!Player.After_Hit)
        return 255;
    flashtime++;
    if (flashtime > 80)
    {
        flashtime = 0;
        Player.After_Hit = false;
        return 255;
    }
    if (flashtime % 20 < 10)
        return 100;
    else
        return 255;
}

void Dino_Hit(bool energy)
{
    if (!energy)
    {
        if (Player.After_Hit || Player.God_Mode)
            return;
        flashtime = 0;
        Player.After_Hit = true;
        health--;
        PlaySound(TEXT("Resources/Audios/HURT.wav"),NULL,SND_FILENAME|SND_ASYNC);
    }
    else{
        if(stamia<3) stamia++;
    }
}

bool Dino_Alive()
{
    if (health <= 0)
    {
        Player.Failed = true;
        return false;
    }
    return true;
}

void Dino_Jump()
{
    if (!Player.InAir && !Player.IsSprint)
    {
        PlaySound(TEXT("Resources/Audios/JUMP.wav"),NULL,SND_FILENAME|SND_ASYNC);
        Player.Velocity = 0;
        Player.Velocity = JUMP_VELOCITY;
        Player.InAir = true;
    }
}

void Dino_Sprint()
{
    if (!Player.InAir)
    {
        Player.IsSprint = true;
        Player.Collision_Box.x = 20;
        Player.Collision_Box.y = 600;
        Player.Collision_Box.w = 200;
        Player.Collision_Box.h = 100;
        Motion_Rate = 4;
    }
    if (Player.InAir)
    {
        Player.Velocity = FALL_VELOCITY;
    }
}

void Dino_DeSprint()
{
    Motion_Rate = 5;
    Player.IsSprint = false;
    Player.Collision_Box.x = 60;
    Player.Collision_Box.y = 540;
    Player.Collision_Box.w = 100;
    Player.Collision_Box.h = 150;
}

void Dino_GodMode(bool isPress)
{
    if (isPress && stamia > 2)
    {
        PlaySound(TEXT("Resources/Audios/GOD.wav"),NULL,SND_FILENAME|SND_ASYNC);
        Player.God_Mode = true;
        stamia=0;
    }
}

void Dino_Update_POS()
{
    if (!Player.Velocity && !Player.InAir)
        return;
    // printf("%d\n", Player.Velocity);
    if (Player.Pos.y - (Player.Velocity) / 60 > GROUND_HEIGHT)
    {
        Player.Collision_Box.y = GROUND_HEIGHT + 40;
        Player.Pos.y = GROUND_HEIGHT;
        Player.InAir = false;
        Player.Velocity = 0;
        return;
    }
    Player.Pos.y -= (Player.Velocity) / 60;
    Player.Collision_Box.y -= (Player.Velocity) / 60;
    Player.Velocity -= GRAVITY;
}

SDL_Texture *Current_Motion()
{
    Dino_Update_POS();
    int rate = Motion_RateCount / Motion_Rate;
    if (Player.Failed)
    {
        return Get_Dino_Text(6);
    }
    if (Player.InAir)
    {
        return Get_Dino_Text(5);
    }
    if (Player.IsSprint)
    {
        if (rate == 0)
            return Get_Dino_Text(3);
        if (rate == 1)
            return Get_Dino_Text(4);
    }
    if (rate == 0)
        return Get_Dino_Text(1);
    if (rate == 1)
        return Get_Dino_Text(2);
    return NULL;
}

void Dino_Display(SDL_Renderer *renderer)
{
    Motion_RateCount++;
    if (Motion_RateCount >= 2 * Motion_Rate)
        Motion_RateCount = 1;
    SDL_Texture *temp = Current_Motion();
    SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(temp, Dino_Getalpha());
    SDL_RenderCopy(renderer, temp, NULL, &(Player.Pos));
}

void UI_Display(SDL_Renderer *renderer)
{
    SDL_Texture *Temp1, *Temp2;
    Temp1 = Get_UI_Text(health);
    Temp2 = Get_UI_Text(stamia + 4);
    SDL_RenderCopy(renderer, Temp1, NULL, &(Heart_Pos));
    SDL_RenderCopy(renderer, Temp2, NULL, &(Stamia_Pos));
}

