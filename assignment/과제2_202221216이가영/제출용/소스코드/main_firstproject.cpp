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


#include "GameFunc.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
Uint32 g_frame_per_sec = 30;

int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();


	g_window = SDL_CreateWindow("First Window", 100, 100, 750, 750, 0); //1280x720
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	InitGame();

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
			continue;

		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	ClearGame();
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}