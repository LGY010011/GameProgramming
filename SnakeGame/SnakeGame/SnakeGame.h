#pragma once
#include "Snake.h"
#include <atlstr.h>
#include <string>

class SnakeGame
{
public:
	SnakeGame();
	~SnakeGame();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();

	//점수 텍스쳐 갱신 함수
	void UpdateScoreTexture();
	//시간 갱신 함수
	void UpdateTimeTexture(int ms);


	int getRunning() {
		return snakeGame_running;
	}

private:
	//게임 시작 및 종료 판단
	int snakeGame_running; //0-게임 시작 전 / 1-게임 중 / 2-게임오버 / 3-일시정지
	int time_ms_;

	//객체 변수
	Snake* snake;
	Item* item;
	Monster* monster;

	//방향키 조작 변수들
	int s_state;//현재 눌린 키 정보 == direction
	bool stop;//정지 정보
	Uint32 last_ticks_;


	////이미지 변수 -------------------------
	//아이템 이미지 변수
	SDL_Texture* item_texture; // the SDL_Texture 
	SDL_Rect item_source_rect; // the rectangle for source image
	SDL_Rect item_destination_rect; // for destination

	//뱀 이미지 변수
	// - 헤드 이미지
	SDL_Texture* snakeHead_texture; // the SDL_Texture 
	SDL_Rect snakeHead_source_rect; // the rectangle for source image
	// - 몸 이미지
	SDL_Texture* snake_texture; // the SDL_Texture 
	SDL_Rect snake_source_rect; // the rectangle for source image

	SDL_Rect snake_destination_rect; // for destination
	//몬스터 이미지 변수
	SDL_Texture* monster_texture; // the SDL_Texture 
	SDL_Rect monster_destination_rect; // the rectangle for source image

	//배경 이미지 변수
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_texture;

	//일시정지 이미지 변수
	SDL_Texture* stop_texture; // the SDL_Texture 
	SDL_Rect stop_destination_rect; // the rectangle for source image

	////폰트 변수 --------------------------------
	TTF_Font* fontK;

	//ready랑 gameover 출력 텍스쳐
	SDL_Texture* ready;
	SDL_Rect read_rect;
	SDL_Texture* over;
	SDL_Rect over_rect;
	SDL_Texture* readme;
	SDL_Rect readme_rect;

	//뱀 길이 숫자 출력 텍스쳐
	SDL_Texture* snake_length; //int형 뱀 길이 출력
	SDL_Rect snake_length_rect;
	SDL_Texture* snake_score; //int형 뱀 길이 출력
	SDL_Rect snake_score_rect;
	
	//게임 시간 출력 텍스쳐
	SDL_Texture* text_time;
	SDL_Rect text_time_rect;


	//지난 시간 텍스쳐
	char text[10]; // 적당한 크기의 문자열 버퍼를 할당합니다.

};