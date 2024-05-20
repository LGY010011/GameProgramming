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

	//���� �ؽ��� ���� �Լ�
	void UpdateScoreTexture();
	//�ð� ���� �Լ�
	void UpdateTimeTexture(int ms);


	int getRunning() {
		return snakeGame_running;
	}

private:
	//���� ���� �� ���� �Ǵ�
	int snakeGame_running; //0-���� ���� �� / 1-���� �� / 2-���ӿ��� / 3-�Ͻ�����
	int time_ms_;

	//��ü ����
	Snake* snake;
	Item* item;
	Monster* monster;

	//����Ű ���� ������
	int s_state;//���� ���� Ű ���� == direction
	bool stop;//���� ����
	Uint32 last_ticks_;


	////�̹��� ���� -------------------------
	//������ �̹��� ����
	SDL_Texture* item_texture; // the SDL_Texture 
	SDL_Rect item_source_rect; // the rectangle for source image
	SDL_Rect item_destination_rect; // for destination

	//�� �̹��� ����
	// - ��� �̹���
	SDL_Texture* snakeHead_texture; // the SDL_Texture 
	SDL_Rect snakeHead_source_rect; // the rectangle for source image
	// - �� �̹���
	SDL_Texture* snake_texture; // the SDL_Texture 
	SDL_Rect snake_source_rect; // the rectangle for source image

	SDL_Rect snake_destination_rect; // for destination
	//���� �̹��� ����
	SDL_Texture* monster_texture; // the SDL_Texture 
	SDL_Rect monster_destination_rect; // the rectangle for source image

	//��� �̹��� ����
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_texture;

	//�Ͻ����� �̹��� ����
	SDL_Texture* stop_texture; // the SDL_Texture 
	SDL_Rect stop_destination_rect; // the rectangle for source image

	////��Ʈ ���� --------------------------------
	TTF_Font* fontK;

	//ready�� gameover ��� �ؽ���
	SDL_Texture* ready;
	SDL_Rect read_rect;
	SDL_Texture* over;
	SDL_Rect over_rect;
	SDL_Texture* readme;
	SDL_Rect readme_rect;

	//�� ���� ���� ��� �ؽ���
	SDL_Texture* snake_length; //int�� �� ���� ���
	SDL_Rect snake_length_rect;
	SDL_Texture* snake_score; //int�� �� ���� ���
	SDL_Rect snake_score_rect;
	
	//���� �ð� ��� �ؽ���
	SDL_Texture* text_time;
	SDL_Rect text_time_rect;


	//���� �ð� �ؽ���
	char text[10]; // ������ ũ���� ���ڿ� ���۸� �Ҵ��մϴ�.

};