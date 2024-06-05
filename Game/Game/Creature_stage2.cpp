#include "Creature_stage2.h"
#include "Phase_stage2Game.h"

//미로----------------------------------------------------------------------------------------------------------------


int Maze::maze[SCREEN_HEIGHT_STAGE2][SCREEN_WIDTH_STAGE2] = {

    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 3, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 3, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 2, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 2, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 2, 1, 1, 3, 1},
    {1, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 3, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 2, 1, 0, 2, 1, 1, 1, 2, 0, 1},
    {1, 0, 2, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 0, 1, 2, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1},
    {1, 0, 1, 1, 0, 3, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 3, 1, 0, 0, 3, 0, 1, 0, 1, 0, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 1, 0, 2, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 1},
    {1, 2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 3, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}


}; // maze 배열 외부 선언

bool Maze::isCoral(int x, int y) {
    return maze[y][x] == 1;
}

//산호----------------------------------------------------------------------------------------------------------------
Coral::Coral(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {

}

void Coral::Draw() {
}

void Coral::attackDamage(int attackPower) {

}

void Coral::move(int newX, int newY) {
}

void Coral::GetAttackted(int damage) {

}

Coral::~Coral() {
}

//산호2----------------------------------------------------------------------------------------------------------------
Coral2::Coral2(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {

}


void Coral2::Draw() {
}

void Coral2::attackDamage(int attackPower) {

}

void Coral2::move(int newX, int newY) {
}

void Coral2::GetAttackted(int damage) {

}
Coral2::~Coral2() {
}

//소라게----------------------------------------------------------------------------------------------------------------

Conch::Conch(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY) {//init 함수 -> 초기값 설정


    moveCounter = 0;

}

void Conch::Draw() {

}

void Conch::GetAttackted(int damage) {

}


void Conch::move(int newX, int newY) {
    // 움직임 카운터를 증가시킴
    moveCounter++;

    // 움직임 카운터가 일정 값에 도달하면 움직임을 수행하고 카운터를 리셋
    if (moveCounter >= MOVE_DELAY) {
        int x = getX();
        int y = getY();

        // 랜덤하게 방향 선택
        direction = rand() % 4;

        // 선택된 방향에 따라 이동
        switch (direction) {
        case 0: // 상
            y--;
            break;
        case 1: // 하
            y++;
            break;
        case 2: // 좌
            x--;
            break;
        case 3: // 우
            x++;
            break;
        }

        // 맵의 경계를 벗어나면 반대 방향으로 이동
        if (x < 0) {
            x = 0;
            direction = 3; // 우로 방향 변경
        }
        else if (x >= SCREEN_WIDTH_STAGE2) {
            x = SCREEN_WIDTH_STAGE2 - 1;
            direction = 2; // 좌로 방향 변경
        }
        if (y < 0) {
            y = 0;
            direction = 1; // 하로 방향 변경
        }
        else if (y >= SCREEN_HEIGHT_STAGE2) {
            y = SCREEN_HEIGHT_STAGE2 - 1;
            direction = 0; // 상으로 방향 변경
        }

        // 위치 업데이트
        setXY(x, y);

        // 움직임 카운터 리셋
        moveCounter = 0;
    }
}

void Conch::attackDamage(int attackPower) {


}


Conch::~Conch() {

}


//거북이----------------------------------------------------------------------------------------------------------------
Turtle::Turtle(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower), turtle_invincible(false), invincible_timer(0), invincible_duration(180) {
    //생성자

}

void Turtle::Draw() {

}

//거북이가 공격받았을때
void Turtle::GetAttackted(int damage) {
    if (!isInvincible()) { // 무적 상태가 아닐 때만 피해를 받음
        cout << "거북이가 공격받았습니다." << endl;
        int hp = getHealth();
        hp -= damage;
        if (hp <= 0) {
            hp = 0; // 거북이 죽음
        }
        setHealth(hp);
        setInvincible(true); // 무적 상태로 설정
        setInvincibleTimer(invincible_duration); // 타이머 설정
    }
}

// 거북이 이동 메서드
void Turtle::move(int newX, int newY) {
    // 새로운 위치가 미로 경계 내에 있는지 확인
    if (newX >= 0 && newX < SCREEN_WIDTH_STAGE2 && newY >= 0 && newY < SCREEN_HEIGHT_STAGE2) {
        // 새로운 위치가 산호인지 확인
        if (Maze::isCoral(newX, newY)) {
            // 산호에 부딪혔으므로 피해를 받고 이동하지 않음
            this->GetAttackted(1);
        }
        else {
            // 산호가 아니라면 거북이를 새로운 위치로 이동
            this->setXY(newX, newY);
        }
    }

}




void Turtle::attackDamage(int attackPower) {
}

bool Turtle::isCollision_Coral(Coral* coral) {
    bool isCollision = false;//충돌여부
    //거북이와 산호의 좌표가 같으면 충돌
    if (this->getX() == coral->getX() && this->getY() == coral->getY()) {
        isCollision = true;

    }
    return isCollision;

}
bool Turtle::isCollision_Coral2(Coral2* coral2) {
    bool isCollision = false;//충돌여부
    //거북이와 산호의 좌표가 같으면 충돌
    if (this->getX() == coral2->getX() && this->getY() == coral2->getY()) {
        isCollision = true;

    }
    return isCollision;

}
bool Turtle::isCollision_Rabbit(Rabbit* rabbit) {
    bool isCollision = false;//충돌여부
    //거북이와 토끼의 좌표가 같으면 충돌
    if (this->getX() == rabbit->getX() && this->getY() == rabbit->getY()) {
        isCollision = true;
        // setIsFace 메서드 호출
        rabbit->setIsFace(!rabbit->getIsFace());
    }
    return isCollision;
}

bool Turtle::isCollision_Conch(Conch* Conch) {
    bool isCollision = false;//충돌여부
    //거북이와 소라게의 좌표가 같으면 충돌
    if (this->getX() == Conch->getX() && this->getY() == Conch->getY()) {
        isCollision = true;
    }
    return isCollision;
}


//소멸자정의
Turtle::~Turtle() {}

//토끼----------------------------------------------------------------------------------------------------------------
Rabbit::Rabbit(int x, int y, int speed, double health) : bellAndRabbit(x, y, speed, health) {

}

void Rabbit::Draw() {
}

void Rabbit::GetAttackted(int damage) {
}

void Rabbit::move(int newX, int newY) {
}
void Rabbit::spawn() {
    // 스폰할 수 있는 위치 목록 생성
    int rabbitSpawnTimer;
    vector<pair<int, int>> validPositions;

    for (int y = 0; y < SCREEN_HEIGHT_STAGE2; ++y) {
        for (int x = 0; x < SCREEN_WIDTH_STAGE2; ++x) {
            if (Maze::maze[y][x] == 0) { // 산호가 아닌 위치 확인
                validPositions.push_back(make_pair(x, y));
            }
        }
    }

    if (!validPositions.empty()) {
        // 랜덤으로 유효한 위치 선택
        uniform_int_distribution<int> distribution(0, validPositions.size() - 1);
        int index = distribution(generator);
        this->setXY(validPositions[index].first, validPositions[index].second);
    }


}


Rabbit::~Rabbit() {}