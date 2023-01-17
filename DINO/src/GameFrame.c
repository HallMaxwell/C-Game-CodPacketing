#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#include "Resource.h"
#include "Background.h"
#include "Dino.h"
#include "Projectile.h"
#include "Fireball.h"

#pragma comment(lib,"winmm.lib")

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

#define FRAMERATE 60

#undef main

SDL_Window *Window;
SDL_Surface *Surface;
SDL_Renderer *Renderer;

SDL_Rect WindowRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

//背景组件
Background *LAYER_GROUND;
Background *LAYER_CLOUD;
Background *LAYER_MOON;
Background *LAYER_STAR;

//游戏函数
int Setspeed;
int Setspeedsaver;
bool Gameover;
bool Gamewelcome = true;
bool Gamepause;

//按键状态
bool SPACE_Pressed;
bool DOWN_Pressed;
bool RESTART_Pressed;
bool Attack;

// UI用户交互
int Score;
int HighScore = 0;

//障碍物
int Timer_Obstacle;
Projectiles *Obstacle[10];

// Attack
Fireball *Fire[5];

void Event_Loop();
void Var_Init();
void DestroyEverything();
void QuitGame();

void GameoverPanel();
void Pause_Game();

void Test_Collision();

void Background_Init();

void Key_Intereact();

bool Projectile_Available(Projectiles *p);

void Sound_Score();

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Window = SDL_CreateWindow("Runz's Dino", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    while (1)
    {
        Var_Init();
        SDL_SetRenderDrawColor(Renderer, 32, 33, 36, 255);
        SDL_RenderClear(Renderer);
        SDL_RenderPresent(Renderer);

        Resource_Load(Renderer);

        Background_Init();
        Dino_Init();

        Event_Loop();

        DestroyEverything();
    }
    QuitGame();
    return 0;
}

void Event_Loop()
{
    while (1)
    {
        int Begin_Tick = SDL_GetTicks(); //获得事件开始时Tick

        SDL_RenderClear(Renderer);
        /*--------------Background_Motion--------------*/
        if(Gamepause){
            Update_Background(Renderer, LAYER_STAR, 0);
            Update_Background(Renderer, LAYER_MOON, 0);
            Update_Background(Renderer, LAYER_CLOUD, 0);
            Update_Background(Renderer, LAYER_GROUND, 0);
            Pause_Game();
        }
        else{
            Update_Background(Renderer, LAYER_STAR, Setspeed);
            Update_Background(Renderer, LAYER_MOON, Setspeed);
            Update_Background(Renderer, LAYER_CLOUD, Setspeed);
            Update_Background(Renderer, LAYER_GROUND, Setspeed);
        }

        if (!Gamepause)
        {
            /*--------------Dino_Motion-------------------*/
            Dino_Display(Renderer);

            if (Gamewelcome)
            {
                Print_Font2(Renderer, -1);
                Setspeed = 0;
            }
            if (Gameover)
            {
                Print_Font2(Renderer, -2);
            }

            if (Gamewelcome && SPACE_Pressed)
            {
                Gamewelcome = false;
                Setspeed = 2;
            }
            if (!Gameover)
            {
                if (!Gamewelcome)
                {
                    /*------------------Attack-------------------------*/
                    for (int i = 0; i < 3; i++)
                    {
                        if (Fire[i] == NULL || Fire[i]->POS.x > WINDOW_WIDTH)
                        {
                            continue;
                        }
                        FireballDisplay(Renderer, Fire[i]);
                        for (int j = 0; j < 5; j++)
                        {
                            if (Obstacle[j] != NULL)
                            {
                                if (Obstacle[j]->POS.x > 0 && Obstacle[j]->POS.x < WINDOW_WIDTH)
                                    if (Fireball_Hit(Fire[i], &(Obstacle[j]->Collision_Box)))
                                    {
                                        Fire[i]->POS.x = 1800;
                                        Obstacle[j]->POS.x = -500;
                                        break;
                                    }
                            }
                        }
                    }
                    if (Attack)
                    {
                        if (Dino_Get_Stamia() > 0)
                        {
                            PlaySound(TEXT("Resources/Audios/SHOOT.wav"),NULL,SND_FILENAME|SND_ASYNC);
                            Dino_Use_Stamia();
                            for (int i = 0; i < 3; i++)
                            {
                                if (Fire[i] == NULL || Fire[i]->POS.x > WINDOW_WIDTH || Fire[i]->POS.y < 0)
                                {
                                    Fireball_Destory(Fire[i]);
                                    Fire[i] = Fireball_Create(Dino_Get_Mouth());
                                    break;
                                }
                            }
                        }
                        Attack = false;
                    }
                    /*--------------Obscatles--------------*/
                    for (int i = 0; i < 5; i++){
                        Projectile_Display(Renderer, Obstacle[i],Setspeed);
                    }
                    Timer_Obstacle++;
                    if (Timer_Obstacle > (180 / Setspeed))
                    {
                        int chance = rand() % 10 + 1;
                        if (chance <= 3)
                        {
                            int index = rand() % 9 + 1;
                            // printf("%d\n",chance);
                            for (int i = 0; i < 5; i++)
                                if (Projectile_Available(Obstacle[i]))
                                {
                                    Obstacle[i] = Projectile_Summon(Renderer, index, WINDOW_WIDTH, WINDOW_HEIGHT, Setspeed);
                                    break;
                                }
                            Timer_Obstacle = 0;
                        }
                    }
                    /*-------------Scores and Speed--------------------*/
                    Score += Setspeed - 1;
                    if (Dino_SpeedUp())
                        Score += Setspeed - 1;
                    if (Score > HighScore)
                        HighScore = Score;
                    Print_Font(Renderer, Score / 15, HighScore / 15);

                    if (Score > 3000&&Score<3010){
                        Setspeed = 3;
                    }

                    if (Score > 6000&&Score<6010){
                        Setspeed = 4;
                    }


                    /*---------------GameOver------------------------*/
                    if (!Dino_Alive())
                    {
                        GameoverPanel();
                    }
                }

                /*--------------------UI-------------------------*/
                if (!Gameover && !Gamewelcome)
                    UI_Display(Renderer);
            }
        }
        /*---------------UpdateRenderer-----------------*/
        SDL_RenderPresent(Renderer);

        /*-----------------Events-------------------*/
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            SDL_KeyCode INPUT = event.key.keysym.sym;
            switch (event.type)
            {
            case SDL_KEYDOWN:

                if (INPUT == SDLK_DOWN)
                {
                    DOWN_Pressed = true;
                }
                if (INPUT == SDLK_SPACE)
                {
                    SPACE_Pressed = true;
                }
                if (INPUT == SDLK_UP)
                {
                    SPACE_Pressed = true;
                }
                if (INPUT == SDLK_LEFT)
                {
                    Dino_GodMode(true);
                }
                if (INPUT == SDLK_RIGHT)
                {
                    Attack = true;
                }
                if (INPUT == SDLK_r)
                {
                    if (Gameover)
                        RESTART_Pressed = true;
                }
                if (INPUT == SDLK_ESCAPE)
                {
                    if(!Gameover&&!Gamewelcome)
                    Gamepause = !Gamepause;
                }
                break;
            case SDL_KEYUP:
                if (INPUT == SDLK_DOWN)
                {
                    DOWN_Pressed = false;
                    Dino_DeSprint();
                }
                if (INPUT == SDLK_SPACE)
                {
                    SPACE_Pressed = false;
                }
                if (INPUT == SDLK_UP)
                {
                    SPACE_Pressed = false;
                }
                if (INPUT == SDLK_LEFT)
                {
                    Dino_GodMode(false);
                }
                break;
            case SDL_QUIT:
                DestroyEverything();
                QuitGame();
                return;
                break;
            default:
                break;
            }
        }
        if (RESTART_Pressed && Gameover)
        {
            break;
        }
        Key_Intereact();

        /*-----------------Framerate-------------------*/
        int End_Tick = SDL_GetTicks(); //获得事件结束Tick
        int Delay_time = 1000 / FRAMERATE - (End_Tick - Begin_Tick);
        if (Delay_time < 0)
            Delay_time = 0;
        SDL_Delay(Delay_time);
    }
}

void Var_Init()
{
    srand(time(0));
    Setspeed = 2;
    Score = 0;
    Timer_Obstacle = 0;
    SPACE_Pressed = false;
    DOWN_Pressed = false;
    RESTART_Pressed = false;
    Gameover = false;
    Gamepause = false;
    memset(Obstacle, 0, sizeof(Obstacle));
    memset(Fire, 0, sizeof(Fire));
}

void DestroyEverything()
{
    Resource_Unload();

    Destroy_Background(LAYER_GROUND);
    Destroy_Background(LAYER_CLOUD);
    Destroy_Background(LAYER_MOON);
    Destroy_Background(LAYER_STAR);
}

void QuitGame()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}

void GameoverPanel()
{
    Setspeed = 0;
    Gameover = true;
}

void Pause_Game(){
    Setspeedsaver=Setspeed;
    Print_Font2(Renderer,-3);
}

void Resume_Game(){
    Setspeed = Setspeedsaver;
    Gamepause= false;
}

void Background_Init()
{
    LAYER_GROUND = Background_Create(1, 8);
    LAYER_CLOUD = Background_Create(2, 4);
    LAYER_MOON = Background_Create(3, 1);
    LAYER_STAR = Background_Create(4, 2);
}

void Key_Intereact()
{
    if (Gameover)
        return;
    if (DOWN_Pressed)
        Dino_Sprint();
    if (SPACE_Pressed)
        Dino_Jump();
}

bool Projectile_Available(Projectiles *p)
{
    if (p == NULL || p->POS.x < -300 || p->POS.x > WINDOW_WIDTH || p->POS.y > WINDOW_HEIGHT || p->POS.y < -200)
    {
        Projectile_Destroy(p);
        return true;
    }
    return false;
}
