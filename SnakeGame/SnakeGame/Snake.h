#pragma once
#include <list>
#include <random>
#include <windows.h>
#include "Snake.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "iostream"

#define GRID 20


extern Uint32 g_frame_per_sec;

extern SDL_Window* window;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern int screenWidth, screenHeight;



using namespace std;

typedef struct Node {
	int x;
	int y;
}Node;

bool checkXY(int x, int y, list<Node*> snakeList);

class Monster { //���̶� �浹�ϸ� �� ���� �ϳ� ����.
private:
	//�����ϰ� ������ ��ġ���� �¿� Ȥ�� ���Ʒ��� ������
	int x;
	int y;
	int direction;
	int mainX;

public:
	Monster(list<Node*> snakeList);
	~Monster();

	int getX() { return x; }
	int getY() { return y; }

	void move();
};

class Item {
private:
	int x;
	int y;
	int itemPower;
	


public:
	Item(list<Node*> snakeList);
	~Item();

	//getter
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getItemPower() {
		return itemPower;
	}
	
	void spawn(list<Node*> snakeList);
};

class Snake {
private:
	list<Node*> snakeList; //snake�� ����
	int snakeLength; //snake ���� -> ������ 1
	int direction;
	Node* prevNode;
	Node* temp;
	bool isFaceMonster;
	
public:
	Snake();
	~Snake();
	//getter
	list<Node*> getSnakeList() {
		return snakeList;
	}
	int getSnakeLength() {
		return snakeLength;
	}

	Node* getSnakeHead() {
		return snakeList.front();
	}
	bool getIsFaceMonster() {
		return isFaceMonster;
	}
	
	
	//set
	void setDirection(int direction) {
		this->direction = direction;
	}
	void setIsFaceMonster(bool set) {
		isFaceMonster = set;
	}
	

	void eatItem(int itemPower);
	void move();
	void decreaseLength();
	
	Node* nextCoordinate(int dircetion);
	//������ ȹ�� ���� Ȯ�� �޼���
	bool isCollidingItem(Item* item, int direction);
	//�ڽ��� ���� �浹�ߴ��� Ȯ��
	bool isCollidingSelf(int direction);
	//���� �浹�ߴ��� Ȯ��
	bool isCollidingWall(int direction);
	//���Ϳ� �浹�ߴ��� Ȯ��
	bool isCollidingMonster(Monster* monster, int direction);
};