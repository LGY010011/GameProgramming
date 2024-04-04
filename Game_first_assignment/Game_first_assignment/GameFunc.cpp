#include "GameFunc.h"
#include <windows.h>
#define M_SIZE 3 //�̻��� ����

using namespace std;

//�̻��� ����ü
typedef struct Missile {
    int x, y; //��ǥ
    bool gone; //�߻翩��
} Missile;

//�̻��� �߻� ���� �Ǵ� �Լ�
bool isGone(Missile* r_list) {
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone)
            return true; //�߻�
    }
    return false; //�̹߻�
}

bool f_list[5];
int f_state;
string f_output;

int r_state;
string r_output;

Missile* r_list = new Missile[M_SIZE];

int countF;

int f_X;
int f_Y;


// �귯�� �ð� ���
double g_elapsed_time_ms;


/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {
    f_state = 4; //stop���� �ʱ�ȭ
    r_state = 0; //0�� �߻� �� �� , 3�̸� �� ����
    r_output = '_';
    f_output = "*"; //����� ��� �ʱ�ȭ
    g_flag_running = true;

    //��� �� ���� ������ �ʱ�ȭ -> stop
    for (int i = 0; i < f_state; i++) {//0�� ����, ...
        f_list[i] = false;
    }
    f_list[f_state] = true;
    countF = 0;

    //�̻��� ��� off
    for (int i = 0; i < M_SIZE; i++)
        r_list[i].gone = false;


    f_X = 15;
    f_Y = 18;
    g_elapsed_time_ms = 0;

    // std::cout ��¿� ���۸� ����Ͽ�, ��� �ӵ��� �������� ������ ���Ѵ�.
    setvbuf(stdout, NULL, _IOLBF, 4096);

    // Clear the console screen.
    // ǥ����� ȭ���� ������ �����.
    system("cls");
}

/////////////////////////////////////////////////////////////
// Update() 
// ������ ������ ������Ʈ�ϴ� �Լ�.
// ���� ������ ���� �����ؾ��ϴ� ��.
// ���ӿ��� �Ͼ�� ��ȭ�� ��� �� ������ �����Ѵ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Update() {
    if (f_state == 0) { //�����̵�
        f_X -= 1;
    }
    else if (f_state == 1) {//�����̵�
        f_X += 1;
    }
    else if (f_state == 2) {//���� �̵�
        f_Y -= 1;
    }
    else if (f_state == 3) {//�Ʒ��� �̵�
        f_Y += 1;
    }

    //����� ���� ����
    if (f_X > 29) {
        f_X = 0;
    }
    else if (f_X < 0) {
        f_X = 29;
    }
    if (f_Y > 19) {
        f_Y = 0;
    }
    else if (f_Y < 0) {
        f_Y = 19;
    }

    //�̻��� ��ġ ����
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) {//�����ִ� �̻����̸� y��ǥ �̵�
            r_output = '!';
            r_list[i].y -= 1;

            if (r_list[i].y < 0) {//�̻����� ������ ������ �ٽ� �����⿡ ����
                r_list[i].gone = false; //i��° �̻����� �����
                r_state -= 1;//�����ִ� �̻��� ���� �ϳ� ����
            }
        }
        else { //�������� ���� �̻����̸� ��ǥ�� �Ҵ�
            r_list[i].x = f_X;
            r_list[i].y = f_Y;
        }
    }

    g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {
    //// 1. ��� �׸���.
    // 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
    // <windows.h>���� �����ϴ� �Լ��� ����Ѵ�.
    COORD cur;
    cur.X = 0;
    cur.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    //// 1.2. ��� �κ��� '_'���� ä���.
    for (int i = 0; i < 20; i++) { //�ళ�� -> ���� 20
        for (int j = 0; j < 30; j++) { //������ -> ���� 30
            cout << "_";
        }
        cout << endl;
    }

    //�̻��� �׸���
    if (isGone(r_list)) {//���� �̻����� ���� ���¶��
        for (int i = 0; i < M_SIZE; i++) {
            if (r_list[i].gone) { //�����ִ� �̻����̶�� �׸���
                cur.X = r_list[i].x;
                cur.Y = r_list[i].y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
                cout << r_output;
                cout.flush();
            }
        }
    }

    //����� �׸���
    cur.X = f_X;
    cur.Y = f_Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
    cout << f_output;

    //// 3. ������ �ϼ�.
    // std::cout���� ����� ���� ��, ���� ȭ�鿡 ǥ�õ� �ʰ� ���ۿ� ���� �ִ� ���� �ִٸ�, ��� ȭ�鿡 ��µǵ��� �Ѵ�.
    cout.flush();
}

/////////////////////////////////////////////////////////////
// HandleEvents() 
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = 0;
                f_list[f_state] = true;

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = 1;
                f_list[f_state] = true;

            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = 2;
                f_list[f_state] = true;

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = 3;
                f_list[f_state] = true;

            }

            else if (event.key.keysym.sym == SDLK_SPACE && r_state < 3) {//�����̽� ������ �̻��� ����

                //�̻��� ������ Ű ���� ������ �����̴� �������� ��� �̵�
                r_state += 1; //���� �̻��� ���� ����
                for (int i = 0; i < M_SIZE; i++) {
                    if (r_list[i].gone) { //�̹� �����ִ� �̻����̸� continue
                        continue;
                    }
                    else {
                        r_list[i].gone = true; //�̻��� �ϳ� �������Ƿ� true�� ����
                        break;
                    }
                }
            }
            break;

        case SDL_KEYUP:

            if (event.key.keysym.sym == SDLK_LEFT ||
                event.key.keysym.sym == SDLK_RIGHT ||
                event.key.keysym.sym == SDLK_UP ||
                event.key.keysym.sym == SDLK_DOWN) {

                countF = 0;
                for (int i = 0;i < 4;i++) {
                    if (i == f_state) {
                        continue;
                    }
                    if (f_list[i]) {
                        f_list[i] = false;
                        countF++;
                    }
                }
                if (countF == 0) {
                    f_list[f_state] = false;
                    f_state = 4;
                    f_list[f_state] = true;
                }
            }
            break;

        default:
            break;

        }
    }
}

/////////////////////////////////////////////////////////////
// ClearGame() 
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame() {
    delete[] r_list;
}
