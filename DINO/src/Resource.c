#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "Resource.h"

//字体
#define FONT_TTF "Resources/TEXTS.ttf"
TTF_Font *font_score;
TTF_Font *font_log;
SDL_Texture *font_text;
SDL_Texture *font_text2;
SDL_Texture *font_text3;
SDL_Texture *font_text4;
SDL_Color font_color;
SDL_Rect Score_Rect;
SDL_Rect HiScore_Rect;
SDL_Rect Gamestart_Rect;
SDL_Rect Gameover_Rect;
SDL_Rect Gameover_Rect2;
char *score_str,*hiscore_str;

//背景相关
#define LAYER_GROUND_PNG "Resources/Textures/LAYER_GROUND.png"
#define LAYER_CLOUD_PNG "Resources/Textures/LAYER_CLOUD.png"
#define LAYER_MOON_PNG "Resources/Textures/LAYER_MOON.png"
#define LAYER_STAR_PNG "Resources/Textures/LAYER_STAR.png"
SDL_Texture *LAYER_GROUND_TEXT;
SDL_Texture *LAYER_CLOUD_TEXT;
SDL_Texture *LAYER_MOON_TEXT;
SDL_Texture *LAYER_STAR_TEXT;

//小恐龙相关
#define Run1_PNG "Resources/Textures/Run1.png"
#define Run2_PNG "Resources/Textures/Run2.png"
#define Sprint1_PNG "Resources/Textures/Sprint1.png"
#define Sprint2_PNG "Resources/Textures/Sprint2.png"
#define Idle_PNG "Resources/Textures/Idle.png"
#define Fail_PNG "Resources/Textures/Fail.png"
SDL_Texture *Run1_TEXT;
SDL_Texture *Run2_TEXT;
SDL_Texture *Sprint1_TEXT;
SDL_Texture *Sprint2_TEXT;
SDL_Texture *Idle_TEXT;
SDL_Texture *Fail_TEXT;

//障碍物
#define Cactus_BIG_1_PNG "Resources/Textures/Cactus_BIG1.png"
#define Cactus_BIG_2_PNG "Resources/Textures/Cactus_BIG2.png"
#define Cactus_MIX_PNG "Resources/Textures/Cactus_MIX.png"
#define Cactus_SMALL_1_PNG "Resources/Textures/Cactus_SMALL1.png"
#define Cactus_SMALL_2_PNG "Resources/Textures/Cactus_SMALL2.png"
#define Cactus_SMALL_3_PNG "Resources/Textures/Cactus_SMALL3.png"
#define Bird1_PNG "Resources/Textures/Bird1.png"
#define Bird2_PNG "Resources/Textures/Bird2.png"
SDL_Texture *Cactus_BIG_1_TEXT;
SDL_Texture *Cactus_BIG_2_TEXT;
SDL_Texture *Cactus_MIX_TEXT;
SDL_Texture *Cactus_SMALL_1_TEXT;
SDL_Texture *Cactus_SMALL_2_TEXT;
SDL_Texture *Cactus_SMALL_3_TEXT;
SDL_Texture *Bird1_TEXT;
SDL_Texture *Bird2_TEXT;


//道具及效果
#define Energy_PNG "Resources/Textures/Energyball.png"
#define Fireball_PNG "Resources/Textures/Fireball.png"
SDL_Texture *Energy_TEXT;
SDL_Texture *Fireball_TEXT;

//UI
#define Heart1_PNG "Resources/Textures/Heart1.png"
#define Heart2_PNG "Resources/Textures/Heart2.png"
#define Heart3_PNG "Resources/Textures/Heart3.png"
#define Stamia0_PNG "Resources/Textures/Stamia0.png"
#define Stamia1_PNG "Resources/Textures/Stamia1.png"
#define Stamia2_PNG "Resources/Textures/Stamia2.png"
#define Stamia3_PNG "Resources/Textures/Stamia3.png"
SDL_Texture *Heart1_TEXT;
SDL_Texture *Heart2_TEXT;
SDL_Texture *Heart3_TEXT;
SDL_Texture *Stamia0_TEXT;
SDL_Texture *Stamia1_TEXT;
SDL_Texture *Stamia2_TEXT;
SDL_Texture *Stamia3_TEXT;


//音频
Uint8 *sound;
Uint32 soundLen;
#define JUMP_WAV "Resources/Audios/JUMP.wav"
#define SCORE_WAV "Resources/Audios/SCORE.wav"
SDL_AudioSpec JUMP_Spec;
SDL_AudioSpec SCORE_Spec;



void Resource_Load(SDL_Renderer *renderer){
    //加载字体
    font_score=TTF_OpenFont(FONT_TTF,32);
    font_log=TTF_OpenFont(FONT_TTF,32);
    font_color.r=255;font_color.g=255;font_color.b=255;font_color.a=255;
    Score_Rect.x=1260;Score_Rect.y=20;Score_Rect.w=100;Score_Rect.h=32;
    HiScore_Rect.x=1400;HiScore_Rect.y=20;HiScore_Rect.w=130;HiScore_Rect.h=32;
    Gamestart_Rect.x=500;Gamestart_Rect.y=300;Gamestart_Rect.w=400;Gamestart_Rect.h=32;
    Gameover_Rect.x=500;Gameover_Rect.y=300;Gameover_Rect.w=550;Gameover_Rect.h=32;
    Gameover_Rect2.x=500;Gameover_Rect2.y=350;Gameover_Rect2.w=500;Gameover_Rect2.h=32;
    score_str=malloc(10*sizeof(char));
    hiscore_str=malloc(10*sizeof(char));


    //加载背景图片
    LAYER_GROUND_TEXT = IMG_LoadTexture(renderer, LAYER_GROUND_PNG);
    LAYER_CLOUD_TEXT = IMG_LoadTexture(renderer, LAYER_CLOUD_PNG);
    LAYER_MOON_TEXT = IMG_LoadTexture(renderer, LAYER_MOON_PNG);
    LAYER_STAR_TEXT = IMG_LoadTexture(renderer, LAYER_STAR_PNG);

    //加载小恐龙图片
    Run1_TEXT = IMG_LoadTexture(renderer, Run1_PNG);
    Run2_TEXT = IMG_LoadTexture(renderer, Run2_PNG);
    Sprint1_TEXT = IMG_LoadTexture(renderer, Sprint1_PNG);
    Sprint2_TEXT = IMG_LoadTexture(renderer, Sprint2_PNG);
    Idle_TEXT = IMG_LoadTexture(renderer, Idle_PNG);
    Fail_TEXT = IMG_LoadTexture(renderer, Fail_PNG);

    //加载障碍物图片
    Cactus_BIG_1_TEXT = IMG_LoadTexture(renderer, Cactus_BIG_1_PNG);
    Cactus_BIG_2_TEXT = IMG_LoadTexture(renderer, Cactus_BIG_2_PNG);
    Cactus_MIX_TEXT = IMG_LoadTexture(renderer, Cactus_MIX_PNG);
    Cactus_SMALL_1_TEXT = IMG_LoadTexture(renderer, Cactus_SMALL_1_PNG);
    Cactus_SMALL_2_TEXT = IMG_LoadTexture(renderer, Cactus_SMALL_2_PNG);
    Cactus_SMALL_3_TEXT = IMG_LoadTexture(renderer, Cactus_SMALL_3_PNG);
    Bird1_TEXT = IMG_LoadTexture(renderer, Bird1_PNG);
    Bird2_TEXT = IMG_LoadTexture(renderer, Bird2_PNG);

    //加载道具及效果图
    Energy_TEXT = IMG_LoadTexture(renderer, Energy_PNG);
    Fireball_TEXT = IMG_LoadTexture(renderer, Fireball_PNG);

    //加载UI
    Heart1_TEXT=IMG_LoadTexture(renderer, Heart1_PNG);
    Heart2_TEXT=IMG_LoadTexture(renderer, Heart2_PNG);
    Heart3_TEXT=IMG_LoadTexture(renderer, Heart3_PNG);
    Stamia0_TEXT=IMG_LoadTexture(renderer, Stamia0_PNG);
    Stamia1_TEXT=IMG_LoadTexture(renderer, Stamia1_PNG);
    Stamia2_TEXT=IMG_LoadTexture(renderer, Stamia2_PNG);
    Stamia3_TEXT=IMG_LoadTexture(renderer, Stamia3_PNG);

    //加载音频
    SDL_LoadWAV(JUMP_WAV,&JUMP_Spec,&sound,&soundLen);
    SDL_LoadWAV(SCORE_WAV,&SCORE_Spec,&sound,&soundLen);
}

void Print_Font(SDL_Renderer *renderer,int score,int hiscore){
    SDL_Surface *font_surf;
    SDL_Surface *font_surf2;
        score_str[0]=score/10000+'0';
        score_str[1]=(score/1000)%10+'0';
        score_str[2]=(score/100)%10+'0';
        score_str[3]=(score/10)%10+'0';
        score_str[4]=score%10+'0';
        score_str[5]='\0';

        hiscore_str[0]='H';hiscore_str[1]='I';
        hiscore_str[2]=' ';
        hiscore_str[3]=hiscore/10000+'0';
        hiscore_str[4]=(hiscore/1000)%10+'0';
        hiscore_str[5]=(hiscore/100)%10+'0';
        hiscore_str[6]=(hiscore/10)%10+'0';
        hiscore_str[7]=hiscore%10+'0';
        hiscore_str[8]='\0';
        font_surf=TTF_RenderUTF8_Blended(font_score,score_str,font_color);
        font_surf2=TTF_RenderUTF8_Blended(font_score,hiscore_str,font_color);
        font_text=SDL_CreateTextureFromSurface(renderer, font_surf);
        font_text2=SDL_CreateTextureFromSurface(renderer, font_surf2);
        SDL_RenderCopy(renderer,font_text2,NULL,&HiScore_Rect);
        SDL_RenderCopy(renderer,font_text,NULL,&Score_Rect);
    SDL_FreeSurface(font_surf);
    SDL_FreeSurface(font_surf2);
    SDL_DestroyTexture(font_text2);
    SDL_DestroyTexture(font_text);
}

void Print_Font2(SDL_Renderer *renderer,int index){
    SDL_Surface *font_surf;
    SDL_Surface *font_surf2;
    if(index==-1)// gamestart
    {
        font_surf=TTF_RenderUTF8_Blended(font_log,"Welcome to Run's Dino!",font_color);
        font_surf2=TTF_RenderUTF8_Blended(font_log,"Press Space to Start Running!",font_color);
        font_text4=SDL_CreateTextureFromSurface(renderer, font_surf);
        font_text3=SDL_CreateTextureFromSurface(renderer, font_surf2);
        SDL_RenderCopy(renderer,font_text3,NULL,&Gameover_Rect2);
        SDL_RenderCopy(renderer,font_text4,NULL,&Gamestart_Rect);
    }
    if(index==-2)// gameover
    {
        font_surf=TTF_RenderUTF8_Blended(font_log,"Oh You are Out of HP...",font_color);
        font_surf2=TTF_RenderUTF8_Blended(font_log,"Press R to Restart!",font_color);
        font_text4=SDL_CreateTextureFromSurface(renderer, font_surf);
        font_text3=SDL_CreateTextureFromSurface(renderer, font_surf2);
        SDL_RenderCopy(renderer,font_text3,NULL,&Gameover_Rect2);
        SDL_RenderCopy(renderer,font_text4,NULL,&Gameover_Rect);
    }
    if(index==-3)// gamepause
    {
        font_surf=TTF_RenderUTF8_Blended(font_log,"Oh You Paused the Game...",font_color);
        font_surf2=TTF_RenderUTF8_Blended(font_log,"Press ESC to Continue!",font_color);
        font_text4=SDL_CreateTextureFromSurface(renderer, font_surf);
        font_text3=SDL_CreateTextureFromSurface(renderer, font_surf2);
        SDL_RenderCopy(renderer,font_text3,NULL,&Gameover_Rect2);
        SDL_RenderCopy(renderer,font_text4,NULL,&Gameover_Rect);
    }

    SDL_FreeSurface(font_surf);
    SDL_FreeSurface(font_surf2);
    SDL_DestroyTexture(font_text3);
    SDL_DestroyTexture(font_text4);
}


SDL_Texture *Get_UI_Text(int index){
    if(index==1) return Heart1_TEXT;
    if(index==2) return Heart2_TEXT;
    if(index==3) return Heart3_TEXT;
    if(index==4) return Stamia0_TEXT;
    if(index==5) return Stamia1_TEXT;
    if(index==6) return Stamia2_TEXT;
    if(index==7) return Stamia3_TEXT;
    return NULL;
}

SDL_Texture *Get_Layer_Text(int index){
    if(index==1) return LAYER_GROUND_TEXT;
    if(index==2) return LAYER_CLOUD_TEXT;
    if(index==3) return LAYER_MOON_TEXT;
    if(index==4) return LAYER_STAR_TEXT;
    return NULL;
}

SDL_Texture *Get_Obstacle_Text(int index){
    if(index==1) return Bird1_TEXT;
    if(index==2) return Bird2_TEXT;
    if(index==3) return Cactus_BIG_1_TEXT;
    if(index==4) return Cactus_BIG_2_TEXT;
    if(index==5) return Cactus_MIX_TEXT;
    if(index==6) return Cactus_SMALL_1_TEXT;
    if(index==7) return Cactus_SMALL_2_TEXT;
    if(index==8) return Cactus_SMALL_3_TEXT;
    if(index==9) return Energy_TEXT;
    if(index==10) return Fireball_TEXT;
    return NULL;
}

SDL_Texture *Get_Dino_Text(int Type){
    if(Type==1) return Run1_TEXT;//run1
    if(Type==2) return Run2_TEXT;//run2
    if(Type==3) return Sprint1_TEXT;//sprint1
    if(Type==4) return Sprint2_TEXT;//sprint2
    if(Type==5) return Idle_TEXT;//idle
    if(Type==6) return Fail_TEXT;//fail
    return NULL;
}

void Resource_Unload(){
    TTF_CloseFont(font_log);
    TTF_CloseFont(font_score);
    SDL_DestroyTexture(font_text2);
    SDL_DestroyTexture(font_text);
    SDL_DestroyTexture(font_text3);
    SDL_DestroyTexture(font_text4);
    free(score_str);
    free(hiscore_str);

    SDL_DestroyTexture(LAYER_CLOUD_TEXT);
    SDL_DestroyTexture(LAYER_MOON_TEXT);
    SDL_DestroyTexture(LAYER_STAR_TEXT);
    SDL_DestroyTexture(LAYER_GROUND_TEXT);

    SDL_DestroyTexture(Run1_TEXT);
    SDL_DestroyTexture(Run2_TEXT);
    SDL_DestroyTexture(Sprint1_TEXT);
    SDL_DestroyTexture(Sprint2_TEXT);
    SDL_DestroyTexture(Idle_TEXT);
    SDL_DestroyTexture(Fail_TEXT);

    SDL_DestroyTexture(Bird1_TEXT);
    SDL_DestroyTexture(Bird2_TEXT);
    SDL_DestroyTexture(Cactus_BIG_1_TEXT);
    SDL_DestroyTexture(Cactus_BIG_2_TEXT);
    SDL_DestroyTexture(Cactus_MIX_TEXT);
    SDL_DestroyTexture(Cactus_SMALL_1_TEXT);
    SDL_DestroyTexture(Cactus_SMALL_2_TEXT);
    SDL_DestroyTexture(Cactus_SMALL_3_TEXT);

    SDL_DestroyTexture(Energy_TEXT);
    SDL_DestroyTexture(Fireball_TEXT);

    SDL_DestroyTexture(Heart1_TEXT);
    SDL_DestroyTexture(Heart2_TEXT);
    SDL_DestroyTexture(Heart3_TEXT);
    SDL_DestroyTexture(Stamia0_TEXT);
    SDL_DestroyTexture(Stamia1_TEXT);
    SDL_DestroyTexture(Stamia2_TEXT);
    SDL_DestroyTexture(Stamia3_TEXT);

    SDL_FreeWAV(sound);
}