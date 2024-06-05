#pragma once

#include <ctime>
#include <random>

//ui ���� �� �� ���ͼ� �Ҵ��ϱ�
//���⼭ ������ ���� ������ phase_stage3, main���� ��� ����

//���⼭ ������ ���� ������ phase_stage3, main���� ��� ����
enum DIRECTION { LEFT, RIGHT, UP, DOWN, STOP };
#include <random>

extern std::default_random_engine generator;

class Creature // �ֻ���
{
private: //�θ��� private �ʵ�� �ڽ� Ŭ�������� ���� �Ұ� -> �޼��带 ���� ������Ʈ�ϰ� �ʱ�ȭ�ϰ� �о�;� ��;;
    int pos_x, pos_y;
    int speed;
    double health;

public:
    Creature() : pos_x(0), pos_y(0), speed(0), health(0) {} //�⺻ ������
    Creature(int x, int y, int speed, double health) {
        //�ڽ� Ŭ������ init �Լ� ȣ��� �̰� ���� ȣ���ؼ� ��ǥ �Ҵ��ϱ�! -> ���������� ��� �Ŵϱ� �𸣰ڴٰ� �ϸ� ������
        pos_x = x;
        pos_y = y;
        this->speed = speed;
        this->health = health;
    }
    //setter��
    void setXY(int x, int y) { //��ǥ ������Ʈ �޼���
        pos_x = x;
        pos_y = y;
    }
    void setX(int x) { //x��ǥ ������Ʈ �޼���
        pos_x = x;
    }
    void setY(int y) { //y��ǥ ������Ʈ �޼���
        pos_y = y;
    }
    void setSpeed(int speed) { //���ǵ� ������Ʈ => speed �����ϴ� ��ü ������ ���߿� �����յ��
        this->speed = speed;
    }
    int getSpeed() {
        //���ǵ� ������Ʈ => speed �����ϴ� ��ü ������ ���߿� �����յ��
        return speed;
    }
    void setHealth(int health) { //HP ������Ʈ �޼���
        this->health = health;
    }
    //getter -> �ϴ� health�� x,y �س���
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

//�ź��� �������� �ε鷹 ��ġ
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

//���Ƹ� ���� ������
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
    void setTargetXY(int x, int y) { //Ÿ�� ��ǥ setter
        this->target_x = x;
        this->target_y = y;
    }
    int getTargetX() { //Ÿ�� x��ǥ getter
        return this->target_x;
    }
    int getTargetY() { //Ÿ�� y��ǥ getter
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


//��, �䳢
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