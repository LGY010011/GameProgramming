#include "Snake.h"

default_random_engine generator;

//Item �޼��� ���� -----------------------------------
Item::Item(list<Node*> snakeList) {
    std::cout << "������ ��ü ����" << std::endl;
    //�����ϰ� ��ġ �����ϴµ� snake�� ��ġ�� �ȵ�
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2);//0~8������ ����
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2); //0~7������ ����
   
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
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID - 2);//0~9������ ����
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 2); //0~7������ ����

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
    newNode->x = ((screenWidth / GRID) / 2)*GRID; //�߾�
    newNode->y = ((screenHeight / GRID) / 2)*GRID; //�߾�
    //cout << newNode->x << ", " << newNode->y << endl;
    snakeList.push_front(newNode);

    prevNode = NULL;
}

// ������ ȹ�� ���� Ȯ�� �޼���
bool Snake::isCollidingItem(Item* item) {
    Node* head = snakeList.front(); // snake�� �Ӹ��� ������
    if (head->x == item->getX() && head->y == item->getY()) {
        return true; // �����۰� �Ӹ��� ���� ��ġ�� �ִٸ� �浹
    }
    return false;
}

// �ڽ��� ���� �浹�ߴ��� Ȯ��
bool Snake::isCollidingSelf() {
    Node* head = snakeList.front(); // snake�� �Ӹ��� ������
    for (auto it = next(snakeList.begin()); it != snakeList.end(); ++it) {
        if (head->x == (*it)->x && head->y == (*it)->y) {
            return true; // �Ӹ��� ������ ��� �κ��̶� ���� ��ġ�� �ִٸ� �浹
        }
    }
    return false;
}

// ���� �浹�ߴ��� Ȯ��
bool Snake::isColldingWall() {
    Node* head = snakeList.front(); // snake�� �Ӹ��� ������
    if (head->x < 0+GRID || head->x >= screenWidth-GRID || head->y < 0+GRID || head->y >= screenHeight-GRID) {
        return true; // �Ӹ��� ȭ�� �ۿ� �ִٸ� ���� �浹
    }
    return false;
}

void Snake::eatItem(int itemPower) {
    //�������� �Ծ��� ��� ���� ����
    snakeLength += itemPower;

    /*
    Node* tail = snakeList.back(); //���� ��� ��ǥ Ȯ�ο�
    //itemPower��ŭ ���� �߰�
    Node* newNode = new Node; //�������� �Ծ��� �� �߰��� ������ ���� ���� �ʵ��� => �ϴ� ���߿�
    newNode->x = tail->x;
    newNode->y = tail->y;
    switch (direction) {
    case 0://���� �̵� ���̸� tail����� �����ʿ� �ϳ� �߰�
        newNode->x+=(GRID*itemPower);
        break;
    case 1://������ �̵� ���̸� tail ����� ���ʿ� �ϳ� �߰�
        newNode->x -= (GRID * itemPower);
        break;
    case 2://���� �̵� ���̸�
        newNode->y += (GRID * itemPower);
        break;
    case 3:
        newNode->y -= (GRID * itemPower);
        break;
    default:
        break;
    }
    snakeList.push_back(newNode);*/

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
    //back���� ��� ����
    /*Node* tail = snakeList.back();
    delete tail;
    snakeList.pop_back();*/
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
}