#pragma once
#include "Game.h"

//>>추가한 변수들
extern TTF_Font* font;
extern SDL_Texture* fame_texture;
extern SDL_Rect frame_destination;


//>> 기존 변수
extern int g_current_game_phase;
extern int g_prev_game_phase;

extern bool g_flag_running;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern int screenWidth, screenHeight;
extern int game_result;
