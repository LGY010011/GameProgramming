#include <iostream>
#include <SDL.h>
#include "SnakeGame.h"

using namespace std;

bool g_flag_running;
Uint32 g_last_time_ms;
SDL_Renderer* g_renderer;
SDL_Window* window;

// 대쉬 속도와 일반 속도를 정의합니다.
const int NORMAL_SPEED = 150; // 일반 속도
Uint32 move_interval = NORMAL_SPEED; // 뱀이 움직이는 간격

int screenWidth, screenHeight;

int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//윈도우 크기 픽셀 : 1060x700 => 53x35
	//wdith 3칸은 텍스트 출력에 쓸 거
	window = SDL_CreateWindow("Snake Game", 100, 100, 1100, 700, 0);
	g_renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);//크기 지정
	// 렌더러의 드로우 색상을 검정색으로 설정합니다.
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);

	// 윈도우를 드로우 색상으로 채웁니다.
	SDL_RenderClear(g_renderer);

	SnakeGame* game = new SnakeGame();

	g_last_time_ms = SDL_GetTicks();

	Uint32 last_move_time = SDL_GetTicks(); // 뱀이 마지막으로 움직인 시간

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;
		
		game->HandleEvents();

		// 일정 시간이 지난 후에만 뱀을 움직입니다.
		if (cur_time_ms - last_move_time >= move_interval) {
			game->Update();
			last_move_time = cur_time_ms;
		}

		game->Render();

		g_last_time_ms = cur_time_ms;
	}

	delete game;
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}