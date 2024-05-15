#pragma once

#include<iostream>
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

// Game Phases
const int PHASE_INTRO=0;
const int PHASE_STAGE=1;
const int PHASE_ENDING=2;



void InitGame();
void ClearGame();


extern Uint32 g_frame_per_sec;

extern int g_current_game_phase;
extern int g_prev_game_phase;
extern SDL_Window* g_window;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern int screenWidth, screenHeight;

class PhaseInterface
{
public:
	PhaseInterface() {};
	virtual ~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;

};
