#pragma once
#include "Snake.h"

class SnakeGame
{
public:
	SnakeGame();
	~SnakeGame();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();

	void UpdateScoreTexture();

	int getRunning() {
		return snakeGame_running;
	}

private:
	//���� ���� �� ���� �Ǵ�
	int snakeGame_running; //0-���� ���� �� / 1-���� �� / 2-���ӿ���

	//��ü ����
	Snake* snake;
	Item* item;

	//����Ű ���� ������
	int s_state;//���� ���� Ű ���� == direction
	bool stop;//���� ����


	//������ �̹��� ����
	SDL_Texture* item_texture; // the SDL_Texture 
	SDL_Rect item_source_rect; // the rectangle for source image
	SDL_Rect item_destination_rect; // for destination

	//�� �̹��� ����
	SDL_Texture* snakeHead_texture; // the SDL_Texture 
	SDL_Rect snakeHead_source_rect; // the rectangle for source image

	SDL_Texture* snake_texture; // the SDL_Texture 
	SDL_Rect snake_source_rect; // the rectangle for source image

	SDL_Rect snake_destination_rect; // for destination

	//��� �̹��� ����
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_texture;

	//��Ʈ ����
	TTF_Font* fontK;

	//ready�� gameover ��� �ؽ���
	SDL_Texture* ready;
	SDL_Rect read_rect;
	SDL_Texture* over;
	SDL_Rect over_rect;

	//�� ���� ���� ��� �ؽ���
	SDL_Texture* snake_length; //int�� �� ���� ���
	SDL_Rect snake_length_rect;

	//���� �ð� �ؽ���
	char text[10]; // ������ ũ���� ���ڿ� ���۸� �Ҵ��մϴ�.

};