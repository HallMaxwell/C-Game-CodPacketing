#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Resource_Load(SDL_Renderer *renderer);

void Print_Font(SDL_Renderer *renderer,int score,int hiscore);
void Print_Font2(SDL_Renderer *renderer,int index);

SDL_Texture *Get_UI_Text(int index);
SDL_Texture *Get_Layer_Text(int index);
SDL_Texture *Get_Obstacle_Text(int index);
SDL_Texture *Get_Dino_Text(int Type);
SDL_Surface *Get_Icon();

void Resource_Unload();