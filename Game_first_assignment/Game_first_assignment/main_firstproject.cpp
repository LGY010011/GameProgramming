//#include "GameFunc.h"
//
//bool g_flag_running;
//Uint32 g_last_time_ms;
//
//int main(int argc, char* argv[]) {
//
//	// Initializing SDL library
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_Window* window = SDL_CreateWindow("First Window", 100, 100, 800, 600, 0);
//
//	InitGame();
//
//	g_last_time_ms = SDL_GetTicks();
//
//	while (g_flag_running) {
//
//		Uint32 cur_time_ms = SDL_GetTicks();
//
//		if (cur_time_ms - g_last_time_ms < 33)
//			continue;
//
//		HandleEvents();
//		Update();
//		Render();
//
//		// SDL_Delay(30);	// 30 밀리세컨드 기다린다.
//		g_last_time_ms = cur_time_ms;
//	}
//
//	ClearGame();
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//
//	return 0;
//}


#include "Game.h"
#include "GameStage.h"
#include "GameIntro.h"
#include "GameEnding.h"


SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
Uint32 g_frame_per_sec = 30;
int screenWidth, screenHeight;
int g_current_game_phase;
int g_prev_game_phase;


int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	

	g_window = SDL_CreateWindow("MyGame", 100, 100, 1280, 720, 0); //1280x720
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);//크기 지정
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	InitGame();

	g_last_time_ms = SDL_GetTicks();
	//std::cout << "시작" << std::endl;
	PhaseInterface* game_phases[3];

	game_phases[0] = new Intro;
	game_phases[1] = new Stage;
	game_phases[2] = new Ending;

	g_current_game_phase = PHASE_INTRO;
	g_prev_game_phase= PHASE_INTRO;
	

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33) {
			continue;
		}
		

		if (g_prev_game_phase != g_current_game_phase) {
			game_phases[g_current_game_phase]->Reset();
			if (g_current_game_phase == PHASE_ENDING) {//스테이지페이지에서 엔딩페이지로 바뀔 경우 스테이지 페이지 reset
				game_phases[g_prev_game_phase]->Reset();
			}
		}
		g_prev_game_phase = g_current_game_phase;
		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();
		

		g_last_time_ms = cur_time_ms;
	}

	delete game_phases[0];
	delete game_phases[1];
	delete game_phases[2];

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	ClearGame();
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}