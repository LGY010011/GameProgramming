#pragma once
#include "Creature.h"
#include <iostream>
#include <SDL.h>
#include <random>
#define GRID_stage2 30
#define TILE_SIZE 40
#define MOVE_DELAY 10
#define RABBIT_SPAWN_TIME 500
#define CORAL2_SPAWN_TIME 45
#define CORAL3_SPAWN_TIME 25 //=>추가

using namespace std;

//화면 사이즈
const int SCREEN_WIDTH_STAGE2 = 33;
const int SCREEN_HEIGHT_STAGE2 = 20;

//거북이 *
//토끼 ^
//산호 @


//미로
class Maze {
public:
    static int maze[SCREEN_HEIGHT_STAGE2][SCREEN_WIDTH_STAGE2];

    static bool isCoral(int x, int y);
};

//산호

class Coral : public Ally {
private:


public:
    Coral(int x, int y, int speed, double health, int attackPower);
    ~Coral();

    virtual void Draw();
    virtual void attackDamage(int attackPower);
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
};

//산호2
class Coral2 : public Ally {
private:


public:
    Coral2(int x, int y, int speed, double health, int attackPower);
    ~Coral2();

    virtual void Draw();
    virtual void attackDamage(int attackPower);
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
};

//소라게

class Conch : public Monster
{
private:

    int moveCounter;
    int direction = rand() % 4;

public:
    Conch(int x, int y, int speed, double health, int attackPower, int tX, int tY);
    ~Conch();


    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    virtual void attackDamage(int attackPower);




};


//토끼
class Rabbit : public bellAndRabbit {
private:

    int spawnTimer; // 재스폰 타이머
public:
    Rabbit(int x, int y, int speed, double health);
    ~Rabbit();
    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    void spawn();
    int getSpawnTimer() const {
        return spawnTimer;
    }

    void setSpawnTimer(int timer) {
        spawnTimer = timer;
    }
};




//거북이
class Turtle : public Ally {
private:
    bool turtle_invincible; // 거북이의 무적 상태 여부
    int invincible_timer;   // 무적 상태 지속 시간
    int invincible_duration; // 무적 지속 시간 (단위: 프레임)

public:
    Turtle(int x, int y, int speed, double health, int attackPower);
    ~Turtle();


    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    virtual void attackDamage(int attackPower);
    bool isCollision_Coral(Coral* coral);
    bool isCollision_Rabbit(Rabbit* rabbit);
    bool isCollision_Conch(Conch* Conch);
    bool isCollision_Coral2(Coral2* coral2);

    // 거북이의 무적 상태 설정
    void setInvincible(bool invincible) { turtle_invincible = invincible; }
    bool isInvincible() const { return turtle_invincible; }

    void setInvincibleTimer(int timer) { invincible_timer = timer; }
    int getInvincibleTimer() const { return invincible_timer; }


};