#include "Snake.h"

default_random_engine generator;

//Item 메서드 구현 -----------------------------------
Item::Item(list<Node*> snakeList) {
    std::cout << "아이템 객체 생성" << std::endl;
    //랜덤하게 위치 설정하는데 snake랑 겹치면 안됨
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2);//0~8까지의 난수
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2); //0~7까지의 난수
   
    itemPower = 1; //먹으면 1개 증가
    

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //만약 새로 할당한 좌표가 snake의 좌표 중에 있다면 다시 반복
 
}


const bool Item::checkXY(int x,int y, list<Node*> snakeList) {
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


void Item::spawn(list<Node*> snakeList) {
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2);//0~9까지의 난수
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2); //0~7까지의 난수

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //만약 새로 할당한 좌표가 snake의 좌표 중에 있다면 다시 반복

}

Item::~Item() {
    
}



//Snake 메서드 구현---------------------------------------------------------------

Snake::Snake() {
    std::cout << "뱀 객체 생성" << std::endl;
    direction = 4; //4는 정지
    Node* newNode = new Node;
    snakeLength = 1; //뱀 초기 길이는 1로 설정
    newNode->x = ((screenWidth / GRID) / 2)*GRID; //중앙
    newNode->y = ((screenHeight / GRID) / 2)*GRID; //중앙
    //cout << newNode->x << ", " << newNode->y << endl;
    snakeList.push_front(newNode);

    prevNode = NULL;
}

// 아이템 획득 여부 확인 메서드
bool Snake::isCollidingItem(Item* item) {
    Node* head = snakeList.front(); // snake의 머리를 가져옴
    if (head->x == item->getX() && head->y == item->getY()) {
        return true; // 아이템과 머리가 같은 위치에 있다면 충돌
    }
    return false;
}

// 자신의 몸과 충돌했는지 확인
bool Snake::isCollidingSelf() {
    Node* head = snakeList.front(); // snake의 머리를 가져옴
    for (auto it = next(snakeList.begin()); it != snakeList.end(); ++it) {
        if (head->x == (*it)->x && head->y == (*it)->y) {
            return true; // 머리와 몸통의 어느 부분이라도 같은 위치에 있다면 충돌
        }
    }
    return false;
}

// 벽과 충돌했는지 확인
bool Snake::isColldingWall() {
    Node* head = snakeList.front(); // snake의 머리를 가져옴
    if (head->x < 0+GRID || head->x >= screenWidth-GRID || head->y < 0+GRID || head->y >= screenHeight-GRID) {
        return true; // 머리가 화면 밖에 있다면 벽과 충돌
    }
    return false;
}

void Snake::eatItem(int itemPower) {
    //아이템을 먹었을 경우 길이 갱신
    snakeLength += itemPower;

    /*
    Node* tail = snakeList.back(); //꼬리 노드 좌표 확인용
    //itemPower만큼 길이 추가
    Node* newNode = new Node; //아이템을 먹었을 때 추가된 노드들이 벽에 닿지 않도록 => 일단 나중에
    newNode->x = tail->x;
    newNode->y = tail->y;
    switch (direction) {
    case 0://왼쪽 이동 중이면 tail노드의 오른쪽에 하나 추가
        newNode->x+=(GRID*itemPower);
        break;
    case 1://오른쪽 이동 중이면 tail 노드의 왼쪽에 하나 추가
        newNode->x -= (GRID * itemPower);
        break;
    case 2://위로 이동 중이면
        newNode->y += (GRID * itemPower);
        break;
    case 3:
        newNode->y -= (GRID * itemPower);
        break;
    default:
        break;
    }
    snakeList.push_back(newNode);*/

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
        newHeadY+=GRID;
        break;
    default:
        break;
    }

    //front에 새 노드 추가;
    head->x = newHeadX;
    head->y = newHeadY;
    snakeList.push_front(head);
    //back에서 노드 제거
    /*Node* tail = snakeList.back();
    delete tail;
    snakeList.pop_back();*/
    // back에서 노드 제거
    if (prevNode != NULL)
        delete prevNode;
    prevNode = snakeList.back();
    snakeList.pop_back();
}

Snake::~Snake() {
    // snakeList의 모든 노드를 삭제합니다.
    for (auto& node : snakeList) {
        delete node;
    }
    snakeList.clear();
}