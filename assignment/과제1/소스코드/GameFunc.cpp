#include "GameFunc.h"
#include <windows.h>

using namespace std;

int f_state;
string f_output;

int r_state;
string r_output;


int f_X;
int f_Y;
int r_X;
int r_Y;

// 흘러간 시간 기록
double g_elapsed_time_ms;


/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {
	f_state = 0; //stop으로 초기화
	r_state = 0; //0은 발사 안 함
	r_output = '_';
	f_output = "*"; //비행기 모양 초기화
	g_flag_running = true;


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
	if (f_state == 1) { //좌측이동
		f_X -= 1;
	}
	else if (f_state == 2) {//우측이동
		f_X += 1;
	}
	else if (f_state == 3) {//위로 이동
		f_Y -= 1;
	}
	else if (f_state == 4) {//아래로 이동
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


	if (r_state == 0) { //나간 미사일이 없음
		r_X = f_X; //미사일 위치
		r_Y = f_Y;
	}
	else { //미사일이 나가있는 상황
		r_output = '!';
		r_Y -= 1;

		if (r_Y < 0) {
			r_state = 0; //미사일 하나가 사라짐
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

	//// 1.2. 배경 부분을 '.'으로 채운다.
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			cout << "_";
		}
		cout << endl;
	}

	//// 1.3. 배경 아래에 시간을 표시한다,
	//cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl;

	//미사일 그리기
	if (r_state != 0) {//만약 미사일이 나간 상태라면
		cur.X = r_X;
		cur.Y = r_Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
		cout << r_output;
		cout.flush();
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
void HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				f_state = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				f_state = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				f_state = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				f_state = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {//스페이스 누르면 미사일 나감
				r_state=1;
			}
			break;

		case SDL_KEYUP:
			f_state = 0;//up하면 정지
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
void ClearGame()
{
}
