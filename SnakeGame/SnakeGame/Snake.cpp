#include "Snake.h"

default_random_engine generator;

//Item �޼��� ���� -----------------------------------
Item::Item(list<Node*> snakeList) {
    std::cout << "������ ��ü ����" << std::endl;
    //�����ϰ� ��ġ �����ϴµ� snake�� ��ġ�� �ȵ�
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2 -5);//0~8������ ����
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2 -5); //0~7������ ����
   
    itemPower = 1; //������ 1�� ����

    do {
        x = distributionX(generator) * GRID;
        y = distributionY(generator) * GRID;
    } while (checkXY(x, y, snakeList)); //���� ���� �Ҵ��� ��ǥ�� snake�� ��ǥ �߿� �ִٸ� �ٽ� �ݺ�
 
}


const bool Item::checkXY(int x,int y, list<Node*> snakeList) {
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
    std::cout << "�� ��ü ����" << std::endl;
    direction = 4; //4�� ����
    Node* newNode = new Node;
    snakeLength = 1; //�� �ʱ� ���̴� 1�� ����
    newNode->x = GRID+((screenWidth / GRID-5) / 2)*GRID; //�߾�
    newNode->y = GRID+((screenHeight / GRID-2) / 2)*GRID; //�߾�
    //cout << newNode->x << ", " << newNode->y << endl;
    snakeList.push_front(newNode);

    prevNode = NULL;
    temp = NULL;
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
    Node* head = nextCoordinate(direction); //snake ��� ���� ��ġ ���
    if (head->x == item->getX() && head->y == item->getY()) {
        return true; // �����۰� �Ӹ��� ���� ��ġ�� �ִٸ� �浹
    }
    delete head;
    return false;
}

// �ڽ��� ���� �浹�ߴ��� Ȯ��
bool Snake::isCollidingSelf(int direction) {

    Node* head = nextCoordinate(direction);
    for (auto it = next(snakeList.begin()); it != snakeList.end(); ++it) {
        if (head->x == (*it)->x && head->y == (*it)->y) {
            return true; // �Ӹ��� ������ ��� �κ��̶� ���� ��ġ�� �ִٸ� �浹
        }
    }
    delete head;
    return false;
}

// ���� �浹�ߴ��� Ȯ��
bool Snake::isColldingWall(int direction) {
    temp = nextCoordinate(direction);

    // ���� ��ġ�� ���� �浹�ϴ��� Ȯ��
    return temp->x < 0+GRID || temp->x >= screenWidth-GRID*4 
        || temp->y < 0+GRID || temp->y >= screenHeight-GRID;
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
        newHeadY+=GRID;
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

Snake::~Snake() {
    // snakeList�� ��� ��带 �����մϴ�.
    for (auto& node : snakeList) {
        delete node;
    }
    snakeList.clear();

    delete temp;
    delete prevNode;
}