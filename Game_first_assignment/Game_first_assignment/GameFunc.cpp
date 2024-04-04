#include "GameFunc.h"
#include <windows.h>
#define M_SIZE 3 //미사일 개수

using namespace std;

//미사일 구조체
typedef struct Missile {
    int x, y; //좌표
    bool gone; //발사여부
} Missile;

//미사일 발사 여부 판단 함수
bool isGone(Missile* r_list) {
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone)
            return true; //발사
    }
    return false; //미발사
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


// 흘러간 시간 기록
double g_elapsed_time_ms;


/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {
    f_state = 4; //stop으로 초기화
    r_state = 0; //0은 발사 안 함 , 3이면 다 나감
    r_output = '_';
    f_output = "*"; //비행기 모양 초기화
    g_flag_running = true;

    //모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }
    f_list[f_state] = true;
    countF = 0;

    //미사일 모두 off
    for (int i = 0; i < M_SIZE; i++)
        r_list[i].gone = false;


    f_X = 15;
    f_Y = 18;
    g_elapsed_time_ms = 0;

    // std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
    setvbuf(stdout, NULL, _IOLBF, 4096);

    // Clear the console screen.
    // 표준출력 화면을 깨끗히 지운다.
    system("cls");
}

/////////////////////////////////////////////////////////////
// Update() 
// 게임의 내용을 업데이트하는 함수.
// 실제 게임의 룰을 구현해야하는 곳.
// 게임에서 일어나는 변화는 모두 이 곳에서 구현한다.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Update() {
    if (f_state == 0) { //좌측이동
        f_X -= 1;
    }
    else if (f_state == 1) {//우측이동
        f_X += 1;
    }
    else if (f_state == 2) {//위로 이동
        f_Y -= 1;
    }
    else if (f_state == 3) {//아래로 이동
        f_Y += 1;
    }

    //비행기 범위 설정
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

    //미사일 위치 저장
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) {//나가있는 미사일이면 y좌표 이동
            r_output = '!';
            r_list[i].y -= 1;

            if (r_list[i].y < 0) {//미사일이 끝까지 갔으면 다시 전투기에 장착
                r_list[i].gone = false; //i번째 미사일이 사라짐
                r_state -= 1;//나가있는 미사일 개수 하나 감소
            }
        }
        else { //나가있지 않은 미사일이면 좌표값 할당
            r_list[i].x = f_X;
            r_list[i].y = f_Y;
        }
    }

    g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {
    //// 1. 배경 그리기.
    // 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
    // <windows.h>에서 제공하는 함수를 사용한다.
    COORD cur;
    cur.X = 0;
    cur.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    //// 1.2. 배경 부분을 '_'으로 채운다.
    for (int i = 0; i < 20; i++) { //행개수 -> 세로 20
        for (int j = 0; j < 30; j++) { //열개수 -> 가로 30
            cout << "_";
        }
        cout << endl;
    }

    //미사일 그리기
    if (isGone(r_list)) {//만약 미사일이 나간 상태라면
        for (int i = 0; i < M_SIZE; i++) {
            if (r_list[i].gone) { //나가있는 미사일이라면 그리기
                cur.X = r_list[i].x;
                cur.Y = r_list[i].y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
                cout << r_output;
                cout.flush();
            }
        }
    }

    //비행기 그리기
    cur.X = f_X;
    cur.Y = f_Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
    cout << f_output;

    //// 3. 프레임 완성.
    // std::cout으로 출력한 내용 중, 아직 화면에 표시되 않고 버퍼에 남아 있는 것이 있다면, 모두 화면에 출력되도록 한다.
    cout.flush();
}

/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
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

            else if (event.key.keysym.sym == SDLK_SPACE && r_state < 3) {//스페이스 누르면 미사일 나감

                //미사일 나가도 키 눌려 있으면 움직이던 방향으로 계속 이동
                r_state += 1; //나간 미사일 개수 증가
                for (int i = 0; i < M_SIZE; i++) {
                    if (r_list[i].gone) { //이미 나가있는 미사일이면 continue
                        continue;
                    }
                    else {
                        r_list[i].gone = true; //미사일 하나 나갔으므로 true로 변경
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
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame() {
    delete[] r_list;
}
