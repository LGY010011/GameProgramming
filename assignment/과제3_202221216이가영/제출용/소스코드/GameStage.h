#pragma once

#include <windows.h>
#include "Game.h"
#include <string>

//�̻��� ����ü
typedef struct Missile {
	int x, y; //��ǥ
	int to;// 0 - �������� �̵�. 1-�������� �̵�, 2-���� �̵�, 3-�Ʒ��� �̵�
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

	//����Ű ���� ������
	bool f_list[4];
	int f_state;//���� ���� Ű ����
	bool stop;//���� ����

	//�̻��� ���� ������
	int r_state;
	std::string r_output;
	Missile* r_list;
	bool r_push;


	//��ǥ �Ҵ�
	int f_X;
	int f_Y;
	

	//������ �̹��� ����
	SDL_Texture* f_sheet_texture; //���� �̹��� �ؽ��� �����
	SDL_Rect f_destination_rect; // x,y,w,h
	SDL_Rect f_source_rect;

	//�̻��� �̹��� ����
	SDL_Rect r_destination_rect;
	SDL_Texture* r_sheet_texture;
	SDL_Rect r_source_rect;

	//��� �̹��� ����
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	//���� ������
	Mix_Chunk* missile;
	Mix_Chunk* recharge;

	//��Ʈ ����
	TTF_Font* fontK;
	SDL_Texture* g_score_int;
	SDL_Texture* g_score_kr;
	SDL_Rect g_score_int_rect;
	SDL_Rect g_score_kr_rect;


	char text[10]; // ������ ũ���� ���ڿ� ���۸� �Ҵ��մϴ�.
	
	//��ư
	bool button;
	SDL_Rect g_button_rect;
};