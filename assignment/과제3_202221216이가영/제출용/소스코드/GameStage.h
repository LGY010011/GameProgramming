#pragma once

#include <windows.h>
#include "Game.h"
#include <string>

//미사일 구조체
typedef struct Missile {
	int x, y; //좌표
	int to;// 0 - 좌측으로 이동. 1-우측으로 이동, 2-위로 이동, 3-아래로 이동
	bool gone;
} Missile;


class Stage : public PhaseInterface
{
public:
	Stage();
	~Stage();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

	void UpdateScoreTexture();
	

private:

	//방향키 조작 변수들
	bool f_list[4];
	int f_state;//현재 눌린 키 정보
	bool stop;//정지 정보

	//미사일 조작 변수들
	int r_state;
	std::string r_output;
	Missile* r_list;
	bool r_push;


	//좌표 할당
	int f_X;
	int f_Y;
	

	//전투기 이미지 변수
	SDL_Texture* f_sheet_texture; //붙일 이미지 텍스쳐 저장소
	SDL_Rect f_destination_rect; // x,y,w,h
	SDL_Rect f_source_rect;

	//미사일 이미지 변수
	SDL_Rect r_destination_rect;
	SDL_Texture* r_sheet_texture;
	SDL_Rect r_source_rect;

	//배경 이미지 변수
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	//음향 변수들
	Mix_Chunk* missile;
	Mix_Chunk* recharge;

	//폰트 변수
	TTF_Font* fontK;
	SDL_Texture* g_score_int;
	SDL_Texture* g_score_kr;
	SDL_Rect g_score_int_rect;
	SDL_Rect g_score_kr_rect;


	char text[10]; // 적당한 크기의 문자열 버퍼를 할당합니다.
	
	//버튼
	bool button;
	SDL_Rect g_button_rect;
};