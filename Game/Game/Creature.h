#pragma once

#include <ctime>
#include <random>

//ui 적용 시 값 얻어와서 할당하기
//여기서 정의한 전역 변수는 phase_stage3, main에서 사용 가능

//여기서 정의한 전역 변수는 phase_stage3, main에서 사용 가능
enum DIRECTION { LEFT, RIGHT, UP, DOWN, STOP };
#include <random>

extern std::default_random_engine generator;

class Creature // 최상위
{
private: //부모의 private 필드는 자식 클래스에서 접근 불가 -> 메서드를 통해 업데이트하고 초기화하고 읽어와야 함;;
    int pos_x, pos_y;
    int speed;
    double health;

public:
    Creature() : pos_x(0), pos_y(0), speed(0), health(0) {} //기본 생성자
    Creature(int x, int y, int speed, double health) {
        //자식 클래스는 init 함수 호출시 이거 먼저 호출해서 좌표 할당하기! -> 객프설에서 배운 거니까 모르겠다고 하면 슬퍼잉
        pos_x = x;
        pos_y = y;
        this->speed = speed;
        this->health = health;
    }
    //setter들
    void setXY(int x, int y) { //좌표 업데이트 메서드
        pos_x = x;
        pos_y = y;
    }
    void setX(int x) { //x좌표 업데이트 메서드
        pos_x = x;
    }
    void setY(int y) { //y좌표 업데이트 메서드
        pos_y = y;
    }
    void setSpeed(int speed) { //스피드 업데이트 => speed 조절하는 객체 없으면 나중에 삭제합디다
        this->speed = speed;
    }
    int getSpeed() {
        //스피드 업데이트 => speed 조절하는 객체 없으면 나중에 삭제합디다
        return speed;
    }
    void setHealth(int health) { //HP 업데이트 메서드
        this->health = health;
    }
    //getter -> 일단 health랑 x,y 해놓음
    double getHealth() {
        return health;
    }
    int getX() {
        return pos_x;
    }
    int getY() {
        return pos_y;
    }

    virtual void Draw() = 0;
    virtual void GetAttackted(int damage) = 0;
    virtual void move(int newX, int newY) = 0;

};

//거북이 강아지똥 민들레 까치
class Ally : public Creature
{
private:
    int attackPower;
public:
    Ally(int x, int y, int speed, double health, int attackPower) : Creature(), attackPower(attackPower) {
        setXY(x, y);
        setSpeed(speed);
        setHealth(health);
    }
};

//병아리 참새 구렁이
class Monster : public Creature
{
private:
    int attackPower;
    int target_x, target_y;

public:
    Creature* target;
    Monster(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Creature(x, y, speed, health) {
        this->attackPower = attackPower;
        this->target_x = tX;
        this->target_y = tY;
    }
    void setTarget(Creature* newTarget) {
        target = newTarget;
    }
    void setTargetXY(int x, int y) { //타겟 좌표 setter
        this->target_x = x;
        this->target_y = y;
    }
    int getTargetX() { //타겟 x좌표 getter
        return this->target_x;
    }
    int getTargetY() { //타겟 y좌표 getter
        return this->target_y;
    }
    int getAttackPower() {
        return this->attackPower;
    }

    void toTarget() {
        if (getX() < target->getX()) {
            setX(getX() + getSpeed());
        }
        else if (getX() > target->getX()) {
            setX(getX() - getSpeed());
        }

        if (getY() < target->getY()) {
            setY(getY() + getSpeed());
        }
        else if (getY() > target->getY()) {
            setY(getY() - getSpeed());
        }
    }

    int getAttackDamage() { return attackPower; }
    virtual void attackDamage(int attackPower) = 0;
    virtual void GetAttackted(int damage) = 0;
    virtual void move(int newX, int newY) = 0;

};


//종, 토끼
class bellAndRabbit : public Creature
{
private:
    bool isFace = false;
    int count = 0;
public:
    bellAndRabbit(int x, int y, int speed, double health) : Creature(x, y, speed, health) {
        isFace = false;
        count = 0;
    }
    //setter
    void setIsFace(bool isFace) {
        this->isFace = isFace;
    }
    void setCount(int count) {
        this->count = count;
    }
    //getter
    bool getIsFace() {
        return this->isFace;
    }
    int getCount() {
        return this->count;
    }

    virtual void spawn() = 0;
};