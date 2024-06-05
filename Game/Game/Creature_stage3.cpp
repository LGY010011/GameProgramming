#include "Creature_stage3.h"
#include <random>


//구렁이 메서드 구현 -------------------------------------------------------------------------------
Snake::Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY) {//init 함수 -> 초기값 설정
    //구렁이 좌표 초기값 설정 
    //구렁이의 길이는 일단 10개로 지정
    //처음 구렁이는 화면의 중앙에 위치
    int centerX = (screenWidth / GRID_STAGE3) / 2 - 1;
    int centerY = (screenHeight / GRID_STAGE3) / 2 - 1;
    for (int i = 0; i < SNAKESIZE - 1; i++) {
        Node* n = new Node;
        n->sX = i + centerX;
        n->sY = centerY;
        n->dircetion = LEFT;
        snakeList.push_back(n);
    }
    dSnake = LEFT; //구렁이 처음 헤드 방향을 LEFT로 설정

    moveCounter = 0;
    n = 8;
}

void Snake::Draw() { //얘는 뭐하는 함수지

}

void Snake::GetAttackted(int damage) { //생각해보니 구렁이는 데미지를 안 받음

}

bool Snake::isNodeInList(int x, int y) {
    for (const auto& node : snakeList) {
        if (node->sX == x && node->sY == y) {//일치하는 노드가 있으면 true 반환
            return true;
        }
    }
    return false;
}

void Snake::move(int magpieX, int magpieY) { //newX와 newY는 사용하지 않음
    //snake는 랜덤하게 움직임 => 이 함수 안에서 좌표 갱신되도록 수정하기
    //좌, 우, 위, 아래 중 하나가 랜덤하게 결정
    //switch문으로 좌표 갱신
    moveCounter++;
    if (moveCounter < n) { // 5번의 게임 루프마다 한 번씩 움직이도록 변경
        return;
    }
    moveCounter = 0; // 카운터 초기화

    Node* head = new Node;

    //새 좌표 계산

    int sx = snakeList.front()->sX;
    int sy = snakeList.front()->sY;

    int newHeadX = sx;
    int newHeadY = sy;


    // 까치를 따라가는 로직
    if (magpieX > sx) {
        dSnake = RIGHT;
        newHeadX = sx + 1;
    }
    else if (magpieX < sx) {
        dSnake = LEFT;
        newHeadX = sx - 1;
    }
    else if (magpieY > sy) {
        dSnake = DOWN;
        newHeadY = sy + 1;
    }
    else if (magpieY < sy) {
        dSnake = UP;
        newHeadY = sy - 1;
    }

    // 맵 범위 검증
    if (newHeadX < 1 || newHeadX >= screenWidth / GRID_STAGE3 - 1 //맵 너비 검증
        || newHeadY < 1 || newHeadY >= screenHeight / GRID_STAGE3 - 1 || isNodeInList(newHeadX, newHeadY))//맵 높이 검증)
    {
        if (dSnake == RIGHT || dSnake == LEFT) {
            newHeadX = sx;
            newHeadY = (newHeadY + 1) % (screenHeight / GRID_STAGE3);
            dSnake = (dSnake == RIGHT) ? UP : DOWN; // 방향 변경

        }
        else {
            newHeadY = sy;
            newHeadX = (newHeadX + 1) % (screenWidth / GRID_STAGE3);
            dSnake = (dSnake == UP) ? LEFT : RIGHT; // 방향 변경
        }
    }




    //front에 새 노드 추가;
    head->sX = newHeadX;
    head->sY = newHeadY;
    head->dircetion = dSnake;
    snakeList.push_front(head);
    //back에서 노드 제거
    Node* tail = snakeList.back();
    delete tail;
    snakeList.pop_back();
}

void Snake::attackDamage(int attackPower) {
    //구렁이가 까치한테 데미지 주는 메서드 -> 까치의 attacked메서드로 쓰자

}


Snake::~Snake() {
    //snake 메모리 해제
    while (!snakeList.empty()) {
        delete snakeList.front();
        snakeList.pop_front();
    }
}

//폭탄 메서드 구현 --------------------------------------------------------------------------------------
//구렁이 메서드 구현 -------------------------------------------------------------------------------
Bomb::Bomb(int x, int y, int speed, double health, int attackPower, int tX, int tY, int startCount, int middleCount, int lastCount, int type) : Monster(x, y, speed, health, attackPower, tX, tY) {//init 함수 -> 초기값 설정
    //cout << "bomb init" << endl;
    //checkCount가 6이 되는 순간 !을 출력하고 충돌여부 확인 및 어택 
    //checkCount가 0이 되는 순간부터 깜빡거릴거임 -> 0부터 5까지 필요한데 짝수면 출력 홀수면 미출력? 출력
    checkCount = -20;
    this->startCount = startCount;
    this->middleCount = middleCount;
    this->lastCount = lastCount;

    this->type = type;
    //데미지 영역 저장
    int k_y = -1;
    int k_x = -1;
    for (int i = 1; i <= 9; i++) {

        bombRange[i - 1].x = x + k_x;
        bombRange[i - 1].y = y + k_y;

        k_y += 1;

        if (i % 3 == 0) {
            k_y = -1;
            k_x += 1;
        }
    }

}

void Bomb::Draw() { //얘는 뭐하는 함수지

}

void Bomb::GetAttackted(int damage) { //생각해보니 구렁이는 데미지를 안 받음

}


void Bomb::move(int newX, int newY) {
    if (checkCount < 0) { //만약 0보다 작을 경우 까치의 위치값을 가져와서 본인 좌표로 할당한다
        this->setXY(newX, newY);

        int k_y = -1;
        int k_x = -1;
        for (int i = 1; i <= 9; i++) {
            bombRange[i - 1].x = newX + k_x;
            bombRange[i - 1].y = newY + k_y;

            k_y += 1;

            if (i % 3 == 0) {
                k_y = -1;
                k_x += 1;
            }
        }

    }
}


void Bomb::attackDamage(int attackPower) {

}


Bomb::~Bomb() {

}

//까치 메서드 구현 -----------------------------------------------------------------------------

Magpie::Magpie(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower) {
    moveCounter = 0;
    invincible = false;
    countBell = 0;
    lastDamageTime = 0;
    Mix_VolumeChunk(hit_sound, 100);
}

void Magpie::Draw() { //얘는 뭐하는 함수지

}

void Magpie::GetAttackted(int damage) {
    //까치 데미지 받기 -> damage=구렁이 attackPower가져오기
    if (invincible) return; // 무적 상태일 경우
    Mix_PlayChannel(-1, hit_sound, 0);
    double hp = getHealth(); //현재 까치의 hp 가져오기
    hp -= damage;
    if (hp < 0) //만약 죽었으면 0으로 설정
        hp = 0;
    setHealth(hp); //hp에서 damage 받은 값으로 재설정

    invincible = true; // 데미지를 받은 후 무적 상태로 전환
    lastDamageTime = SDL_GetTicks(); // 데미지를 받은 
}

void Magpie::move(int newX, int newY) {
    //newX와 newY 범위 확인은 외부에서 하고 넘긴거 -> 코드 중복됨
    static int moveCounter = 0;
    moveCounter++;

    if (moveCounter % 5 == 0) { // 5번의 호출마다 한 번씩 이동
        this->setXY(newX, newY);
    }

}

void Magpie::attackDamage(int attackPower) {

}

bool Magpie::isCollidingSnake(Snake* snake) { //구렁이와의 충돌 여부 확인 => 이거 트루면 magpie.attacked함수 호출

    bool is = false; //충돌 안 함으로 초기화

    // snake의 모든 노드를 돌며 확인해야 함
    for (const auto& node : snake->getSnakeList()) {
        // 만약 부딪혔으면 true 반환
        if ((node->sX == this->getX()) && (node->sY == this->getY())) {
            is = true;
            break;
        }
    }

    return is;
}

bool Magpie::isCollidingBell(Bell* bell) {
    bool is = false; //충돌 안 함으로 초기화

    if ((this->getX() == bell->getX()) && (this->getY() == bell->getY())) {//충돌조건
        is = true;
        bell->setIsFace(!bell->getIsFace()); // setIsFace 메서드 호출
        bell->setLastEatenTime(SDL_GetTicks()); // 마지막으로 먹은 시간 설정
        bell->setXY(0, 0); //화면에서 사라지도록 설정
    }

    return is;
}

bool Magpie::isCollidingBomb(Bomb* bomb) {

    bool is = false; //충돌 안 함으로 초기화

    int x = this->getX();
    int y = this->getY();

    bombAttack* b = bomb->getBombRange();
    for (int i = 0; i < 9; i++) {
        // 만약 부딪혔으면 true 반환
        if ((b[i].x == x) && (b[i].y == y)) {
            is = true;
            break;
        }
    }

    return is;
}


//종 구현부 -----------------------------------------------------------------------------

Bell::Bell(int x, int y, int speed, double health) : bellAndRabbit(x, y, speed, health) {
    lastEatenTime = 0;
}

void Bell::Draw() {

}
void Bell::GetAttackted(int damage) {
    //Bell은 데미지 안 받음
}
void Bell::move(int newX, int newY) {
    //Bell의 좌표는 움직이지 않음
}
void Bell::spawn() {
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);

    if (this->getIsFace()) { //만약 까치를 만났다면
        //종을 한번에 화면에 뿌릴거면 외부에서 Bell 객체 배열을 만드는게 더 효율적
        //종을 하나 먹을 때마다 랜덤하게 뿌릴 거면 이 방식으로 사용

        this->setIsFace(!this->getIsFace()); //만났던 거 안 만났다고 갱신

        //좌표 갱신 -> 랜덤하게
        this->setXY(distributionX(generator), distributionY(generator));
    }
}


Bell::~Bell() {

}