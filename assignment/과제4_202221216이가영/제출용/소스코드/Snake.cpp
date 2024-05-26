#include "Snake.h"


default_random_engine generator(static_cast<unsigned long>(time(0)));

bool checkXY(int x, int y, list<Node*> snakeList) {
    bool is = false; //�浹 �� ������ �ʱ�ȭ

    // snake�� ��� ��带 ���� Ȯ���ؾ� ��
    for (const auto& node : snakeList) {
        // ���� �ε������� true ��ȯ
        if ((node->x == x) && (node->y == y)) {
            is = true;
            break;
        }
    }

    return is;
}

//monster �޼��� ���� --------------------------------- 
Monster::Monster(list<Node*> snakeList) {
    uniform_int_distribution<int> distributionX(2, screenWidth / GRID - 2 - 5);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2 - 5 -1);

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //���� ���� �Ҵ��� ��ǥ�� snake�� ��ǥ �߿� �ִٸ� �ٽ� �ݺ�

    uniform_int_distribution<int> distribution(0, 3);
    direction = distribution(generator);
}

Monster::~Monster() {
}

void Monster::move() {
    switch (direction) {
    case 0: // �������� �̵�
        x -= GRID;
        break;
    case 1: // ���������� �̵�
        x += GRID;
        break;
    case 2: // ���� �̵�
        y -= GRID;
        break;
    case 3: // �Ʒ��� �̵�
        y += GRID;
        break;
    }

    // ���� ��Ҵ��� Ȯ���ϰ�, ��Ҵٸ� ������ �ٲߴϴ�.
    
    if (x <= GRID) {
        x = GRID;
        direction = 1; // ���������� ������ �ٲߴϴ�.
    }
    else if (x >= screenWidth - GRID * 5) {
        x = screenWidth - GRID * 5;
        direction = 0; // �������� ������ �ٲߴϴ�.
    }
    else if (y <= GRID) {
        y = GRID;
        direction = 3; // �Ʒ��� ������ �ٲߴϴ�.
    }
    else if (y >= screenHeight - GRID*2) {
        y = screenHeight - GRID*2;
        direction = 2; // ���� ������ �ٲߴϴ�.
    }
}

int Monster::nextCoordinate() {
    return x + direction * GRID;
}


//Item �޼��� ���� -----------------------------------
Item::Item(list<Node*> snakeList) {
   
    //�����ϰ� ��ġ �����ϴµ� snake�� ��ġ�� �ȵ�
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2 -5);//0~8������ ����
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2 -5); //0~7������ ����
   
    itemPower = 1; //������ 1�� ����

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //���� ���� �Ҵ��� ��ǥ�� snake�� ��ǥ �߿� �ִٸ� �ٽ� �ݺ�
 
}





void Item::spawn(list<Node*> snakeList) {
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2 -5);//0~9������ ����
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2-5); //0~7������ ����

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //���� ���� �Ҵ��� ��ǥ�� snake�� ��ǥ �߿� �ִٸ� �ٽ� �ݺ�

}

Item::~Item() {
    
}

//Snake �޼��� ����---------------------------------------------------------------

Snake::Snake() {
    direction = 4; //4�� ����
    Node* newNode = new Node;
    snakeLength = 1; //�� �ʱ� ���̴� 1�� ����
    newNode->x = GRID+((screenWidth / GRID-5) / 2)*GRID; //�߾�
    newNode->y = GRID+((screenHeight / GRID-2) / 2)*GRID; //�߾�
    //cout << newNode->x << ", " << newNode->y << endl;
    snakeList.push_front(newNode);

    prevNode = NULL; //���� ���
    temp = NULL; //�ӽ� ���
    isFaceMonster = false;
}

Node* Snake::nextCoordinate(int dircetion) {
    // ���� ��ġ ���
    Node* nextPosition = new Node();
    // �� ��ǥ ���
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

// ������ ȹ�� ���� Ȯ�� �޼���
bool Snake::isCollidingItem(Item* item,int direction) {
    temp = nextCoordinate(direction); //snake ��� ���� ��ġ ���
    if (temp->x == item->getX() && temp->y == item->getY()) {
        //delete temp;
        return true; // �����۰� �Ӹ��� ���� ��ġ�� �ִٸ� �浹
    }
    //delete head;
    return false;
}

// �ڽ��� ���� �浹�ߴ��� Ȯ��
bool Snake::isCollidingSelf(int direction) {
    temp = nextCoordinate(direction);
    for (auto it = next(snakeList.begin()); it != snakeList.end(); ++it) {
        if (temp->x == (*it)->x && temp->y == (*it)->y) {
           // delete head;
            return true; // �Ӹ��� ������ ��� �κ��̶� ���� ��ġ�� �ִٸ� �浹
        }
    }
    //delete head;
    return false;
}

// ���� �浹�ߴ��� Ȯ��
bool Snake::isCollidingWall(int direction) {
    temp = nextCoordinate(direction);

    // ���� ��ġ�� ���� �浹�ϴ��� Ȯ��
    return temp->x < 0+GRID || temp->x >= screenWidth-GRID*4 
        || temp->y < 0+GRID || temp->y >= screenHeight-GRID;
}
    
bool Snake::isCollidingMonster(Monster* monster,int direction) {
    //snake�� �Ӹ��� �ε����� �浹�� �Ǵ�
    //Node* head = nextCoordinate(direction); // ���� �Ӹ��� ������ �̵��� ��ġ�� ����մϴ�.
    temp = nextCoordinate(direction);
    if (temp->x == monster->getX() && temp->y == monster->getY()) {
        //delete head;
        return true; // ���� �Ӹ��� ���Ͱ� ���� ��ġ�� �ִٸ� �浹
    }
    return false;

    //if (!snakeList.empty()) {
    //    Node* head = snakeList.front();
    //    // �� ��ġ�� ������ ��ġ�� ������ Ȯ���մϴ�.
    //    if (head->x == monster->getX() && head->y == monster->getY()) {
    //        //delete head;
    //        return true; // ���� �Ӹ��� ���Ͱ� ���� ��ġ�� �ִٸ� �浹
    //    }
    //   // delete head;
    //}
    //return false;
}

void Snake::eatItem(int itemPower) {
    //�������� �Ծ��� ��� ���� ����
    snakeLength += itemPower;

    // ���� ���� ��带 �ٽ� ���� ������ �߰��մϴ�.
    if (prevNode != NULL) {
        snakeList.push_back(prevNode);
        prevNode = NULL;
    }

}

void Snake::move() {
    //�� ��ǥ ���
    Node* head = new Node;

    //�� ��ǥ ���
    int newHeadX = snakeList.front()->x;
    int newHeadY = snakeList.front()->y;
    
    switch (direction) {
    case 0:
        //x��ǥ
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

    //front�� �� ��� �߰�;
    head->x = newHeadX;
    head->y = newHeadY;
    snakeList.push_front(head);
    
    // back���� ��� ����
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
    // snakeList�� ��� ��带 �����մϴ�.
    for (auto& node : snakeList) {
        delete node;
    }

    snakeList.clear();

    delete temp;
    delete prevNode;
}