#include "Game.h"
#include "Phase_Intro.h"
#include "Phase_stage1Intro.h"
#include "Phase_stage1Game.h"
#include "Phase_stage1Ending.h"
#include "Phase_stage2Intro.h"
#include "Phase_stage2Game.h"
#include "Phase_stage2Ending.h"
#include "Phase_stage3Intro.h"
#include "Phase_stage3Game.h"
#include "Phase_stage3Ending.h"
#include "Phase_Ending.h"
#include "Phase_Gallery.h"
#include "STAGE.h"
#include <Windows.h>

std::default_random_engine generator(static_cast<unsigned long>(time(0)));

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running = true;
Uint32 g_last_time_ms;

SDL_Texture* fame_texture;
SDL_Rect frame_destination;
TTF_Font* font;

// Game Phases
int g_current_game_phase;
int g_prev_game_phase;
int screenWidth = 1080;
int screenHeight = 720;
int game_result = 0;

const int FPS = 60; // desired frame rate
const int frameDelay = 1000 / FPS; // delay in ms for each frame

bool viewedEndings[NUMBER_OF_STAGES][ENDINGS_PER_STAGE] = { {false, false, false}, {false, false, false}, {false, false, false} };

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG); // 이미지 라이브러리 초기화
    TTF_Init();

    font = TTF_OpenFont("../../Resources/PF.ttf", 100);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
        exit(1);
    }

    g_window = SDL_CreateWindow("FolkTale", 100, 100, screenWidth, screenHeight, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, 0);


    InitGame();

    PhaseInterface* game_phase[11];

    game_phase[PHASE_INTRO] = new Intro();
    game_phase[PHASE_STAGE1_INTRO] = new Phase_stage1Intro();
    game_phase[PHASE_STAGE1_GAME] = new Stage1();
    game_phase[PHASE_STAGE1_ENDING] = new Phase_stage1Ending();
    game_phase[PHASE_STAGE2_INTRO] = new Phase_stage2Intro();
    game_phase[PHASE_STAGE2_GAME] = new Stage2();
    game_phase[PHASE_STAGE2_ENDING] = new Phase_stage2Ending();
    game_phase[PHASE_STAGE3_INTRO] = new Phase_stage3Intro();
    game_phase[PHASE_STAGE3_GAME] = new Stage3();
    game_phase[PHASE_STAGE3_ENDING] = new Phase_stage3Ending();
    game_phase[PHASE_GALLERY] = new Gallery();
    game_phase[PHASE_ENDING] = new Ending();

    game_phase[g_prev_game_phase]->Reset();
    g_current_game_phase = PHASE_INTRO;
    g_prev_game_phase = PHASE_INTRO;

    //game_phase[PHASE_STAGE1_GAME]->Reset();

    while (g_flag_running)
    {
        Uint32 cur_time_ms = SDL_GetTicks();
        //Uint32 frameStart = SDL_GetTicks();
        if (cur_time_ms - g_last_time_ms < 33) {
            continue;
        }
        if (g_prev_game_phase != g_current_game_phase) {
            game_phase[g_prev_game_phase]->Reset();
            game_phase[g_current_game_phase]->Reset();
        }

        g_prev_game_phase = g_current_game_phase;
        game_phase[g_current_game_phase]->HandleEvents();
        game_phase[g_current_game_phase]->Update();
        game_phase[g_current_game_phase]->Render();

        g_last_time_ms = cur_time_ms;
        //Uint32 frameTime = SDL_GetTicks() - frameStart;

        //if (frameDelay > frameTime) // if frame finished early
        //{
        //    SDL_Delay(frameDelay - frameTime); // delay the difference
        //}
    }

    delete game_phase[PHASE_INTRO];
    delete game_phase[PHASE_STAGE1_INTRO];
    delete game_phase[PHASE_STAGE1_GAME];
    delete game_phase[PHASE_STAGE1_ENDING];
    delete game_phase[PHASE_STAGE2_INTRO];
    delete game_phase[PHASE_STAGE2_GAME];
    delete game_phase[PHASE_STAGE2_ENDING];
    delete game_phase[PHASE_STAGE3_INTRO];
    delete game_phase[PHASE_STAGE3_GAME];
    delete game_phase[PHASE_STAGE3_ENDING];
    delete game_phase[PHASE_GALLERY];
    delete game_phase[PHASE_ENDING];

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);


    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}