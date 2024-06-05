#include "Snake.h"


default_random_engine generator(static_cast<unsigned long>(time(0)));

bool checkXY(int x, int y, list<Node*> snakeList) {
    bool is = false; //충돌 안 함으로 초기화

    // snake의 모든 노드를 돌며 확인해야 함
    for (const auto& node : snakeList) {
        // 만약 부딪혔으면 true 반환
        if ((node->x == x) && (node->y == y)) {
            is = true;
            break;
        }
    }

    return is;
}

//monster 메서드 구현 --------------------------------- 
Monster::Monster(list<Node*> snakeList) {
    uniform_int_distribution<int> distributionX(2, screenWidth / GRID - 2 - 5);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2 - 5 -1);

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //만약 새로 할당한 좌표가 snake의 좌표 중에 있다면 다시 반복

    uniform_int_distribution<int> distribution(0, 3);
    direction = distribution(generator);
}

Monster::~Monster() {
}

void Monster::move() {
    switch (direction) {
    case 0: // 왼쪽으로 이동
        x -= GRID;
        break;
    case 1: // 오른쪽으로 이동
        x += GRID;
        break;
    case 2: // 위로 이동
        y -= GRID;
        break;
    case 3: // 아래로 이동
        y += GRID;
        break;
    }

    // 벽에 닿았는지 확인하고, 닿았다면 방향을 바꿉니다.
    
    if (x <= GRID) {
        x = GRID;
        direction = 1; // 오른쪽으로 방향을 바꿉니다.
    }
    else if (x >= screenWidth - GRID * 5) {
        x = screenWidth - GRID * 5;
        direction = 0; // 왼쪽으로 방향을 바꿉니다.
    }
    else if (y <= GRID) {
        y = GRID;
        direction = 3; // 아래로 방향을 바꿉니다.
    }
    else if (y >= screenHeight - GRID*2) {
        y = screenHeight - GRID*2;
        direction = 2; // 위로 방향을 바꿉니다.
    }
}

int Monster::nextCoordinate() {
    return x + direction * GRID;
}


//Item 메서드 구현 -----------------------------------
Item::Item(list<Node*> snakeList) {
   
    //랜덤하게 위치 설정하는데 snake랑 겹치면 안됨
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2 -5);//0~8까지의 난수
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2 -5); //0~7까지의 난수
   
    itemPower = 1; //먹으면 1개 증가

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //만약 새로 할당한 좌표가 snake의 좌표 중에 있다면 다시 반복
 
}





void Item::spawn(list<Node*> snakeList) {
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2 -5);//0~9까지의 난수
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2-5); //0~7까지의 난수

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //만약 새로 할당한 좌표가 snake의 좌표 중에 있다면 다시 반복

}

Item::~Item() {
    
}

//Snake 메서드 구현---------------------------------------------------------------

Snake::Snake() {
    direction = 4; //4는 정지
    Node* newNode = new Node;
    snakeLength = 1; //뱀 초기 길이는 1로 설정
    newNode->x = GRID+((screenWidth / GRID-5) / 2)*GRID; //중앙
    newNode->y = GRID+((screenHeight / GRID-2) / 2)*GRID; //중앙
    //cout << newNode->x << ", " << newNode->y << endl;
    snakeList.push_front(newNode);

    prevNode = NULL; //이전 노드
    temp = NULL; //임시 노드
    isFaceMonster = false;
}

Node* Snake::nextCoordinate(int dircetion) {
    // 다음 위치 계산
    Node* nextPosition = new Node();
    // 새 좌표 계산
    nextPosition->x = snakeList.front()->x;
    nextPosition->y = snakeList.front()->y;

    switch (direction) {
    case 0:
        nextPosition->x -= GRID;
        break;
    case 1:
        nextPosition->x += GRID;
        break;
    case 2:
        nextPosition->y -= GRID;
        break;
    case 3:
        nextPosition->y += GRID;
        break;
    default:
        break;
    }

    return nextPosition;
}

// 아이템 획득 여부 확인 메서드
bool Snake::isCollidingItem(Item* item,int direction) {
    temp = nextCoordinate(direction); //snake 헤드 다음 위치 계산
    if (temp->x == item->getX() && temp->y == item->getY()) {
        //delete temp;
        return true; // 아이템과 머리가 같은 위치에 있다면 충돌
    }
    //delete head;
    return false;
}

// 자신의 몸과 충돌했는지 확인
bool Snake::isCollidingSelf(int direction) {
    temp = nextCoordinate(direction);
    for (auto it = next(snakeList.begin()); it != snakeList.end(); ++it) {
        if (temp->x == (*it)->x && temp->y == (*it)->y) {
           // delete head;
            return true; // 머리와 몸통의 어느 부분이라도 같은 위치에 있다면 충돌
        }
    }
    //delete head;
    return false;
}

// 벽과 충돌했는지 확인
bool Snake::isCollidingWall(int direction) {
    temp = nextCoordinate(direction);

    // 다음 위치가 벽과 충돌하는지 확인
    return temp->x < 0+GRID || temp->x >= screenWidth-GRID*4 
        || temp->y < 0+GRID || temp->y >= screenHeight-GRID;
}
    
bool Snake::isCollidingMonster(Monster* monster,int direction) {
    //snake의 머리와 부딪히면 충돌로 판단
    //Node* head = nextCoordinate(direction); // 뱀의 머리가 다음에 이동할 위치를 계산합니다.
    temp = nextCoordinate(direction);
    if (temp->x == monster->getX() && temp->y == monster->getY()) {
        //delete head;
        return true; // 뱀의 머리와 몬스터가 같은 위치에 있다면 충돌
    }
    return false;

    //if (!snakeList.empty()) {
    //    Node* head = snakeList.front();
    //    // 그 위치가 몬스터의 위치와 같은지 확인합니다.
    //    if (head->x == monster->getX() && head->y == monster->getY()) {
    //        //delete head;
    //        return true; // 뱀의 머리와 몬스터가 같은 위치에 있다면 충돌
    //    }
    //   // delete head;
    //}
    //return false;
}

void Snake::eatItem(int itemPower) {
    //아이템을 먹었을 경우 길이 갱신
    snakeLength += itemPower;

    // 이전 꼬리 노드를 다시 뱀의 꼬리에 추가합니다.
    if (prevNode != NULL) {
        snakeList.push_back(prevNode);
        prevNode = NULL;
    }

}

void Snake::move() {
    //새 좌표 노드
    Node* head = new Node;

    //새 좌표 계산
    int newHeadX = snakeList.front()->x;
    int newHeadY = snakeList.front()->y;
    
    switch (direction) {
    case 0:
        //x좌표
        newHeadX-=GRID;
        break;
    case 1:
        newHeadX+=GRID;
        break;
    case 2:
        newHeadY-=GRID;
        break;
    case 3:
        newHeadY += GRID;
        break;
    default:
        break;
    }

    //front에 새 노드 추가;
    head->x = newHeadX;
    head->y = newHeadY;
    snakeList.push_front(head);
    
    // back에서 노드 제거
    if (prevNode != NULL)
        delete prevNode;
    prevNode = snakeList.back();
    snakeList.pop_back();
}

void Snake::decreaseLength() {
    if (!snakeList.empty()) {
        snakeList.pop_back();
        snakeLength -= 1;
    }
}

Snake::~Snake() {
    // snakeList의 모든 노드를 삭제합니다.
    for (auto& node : snakeList) {
        delete node;
    }

    snakeList.clear();

    delete temp;
    delete prevNode;
}