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
	const bool checkXY(int x, int y, list<Node*> snakeList);
	void spawn(list<Node*> snakeList);
};

class Snake {
private:
	list<Node*> snakeList; //snake의 노드들
	int snakeLength; //snake 길이 -> 시작은 1
	int direction;
	Node* prevNode;
	Node* temp;

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
	
	//set
	void setDirection(int direction) {
		this->direction = direction;
	}
	void eatItem(int itemPower);
	void move();
	
	Node* nextCoordinate(int dircetion);
	//아이템 획득 여부 확인 메서드
	bool isCollidingItem(Item* item, int direction);
	//자신의 몸과 충돌했는지 확인
	bool isCollidingSelf(int direction);
	//벽과 충돌했는지 확인
	bool isColldingWall(int direction);
};