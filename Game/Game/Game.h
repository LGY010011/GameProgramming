#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE1_INTRO = 1;
const int PHASE_STAGE1_GAME = 2;
const int PHASE_STAGE1_ENDING = 3;
const int PHASE_STAGE2_INTRO = 4;
const int PHASE_STAGE2_GAME = 5;
const int PHASE_STAGE2_ENDING = 6;
const int PHASE_STAGE3_INTRO = 7;
const int PHASE_STAGE3_GAME = 8;
const int PHASE_STAGE3_ENDING = 9;
const int PHASE_GALLERY = 10;
const int PHASE_ENDING = 11;

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

void InitGame();
void ClearGame();

extern TTF_Font* font;
extern SDL_Texture* fame_texture;
extern SDL_Rect frame_destination;

extern int g_current_game_phase;
extern int g_prev_game_phase;

extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern int screenWidth, screenHeight;
extern int game_result;

// 스테이지 당 엔딩의 수를 선언하는 상수
const int ENDINGS_PER_STAGE = 3;

// 스테이지의 수를 선언하는 상수
const int NUMBER_OF_STAGES = 3; // 실제 스테이지 수로 변경하세요

// 각 스테이지에서 본 엔딩을 저장하는 배열 선언
extern bool viewedEndings[NUMBER_OF_STAGES][ENDINGS_PER_STAGE];