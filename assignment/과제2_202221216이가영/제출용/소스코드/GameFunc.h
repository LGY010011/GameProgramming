#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"



void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();


extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern SDL_Window* g_window;
