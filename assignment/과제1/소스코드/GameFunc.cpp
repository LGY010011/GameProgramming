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

// �귯�� �ð� ���
double g_elapsed_time_ms;


/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {
	f_state = 0; //stop���� �ʱ�ȭ
	r_state = 0; //0�� �߻� �� ��
	r_output = '_';
	f_output = "*"; //����� ��� �ʱ�ȭ
	g_flag_running = true;


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
	if (f_state == 1) { //�����̵�
		f_X -= 1;
	}
	else if (f_state == 2) {//�����̵�
		f_X += 1;
	}
	else if (f_state == 3) {//���� �̵�
		f_Y -= 1;
	}
	else if (f_state == 4) {//�Ʒ��� �̵�
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


	if (r_state == 0) { //���� �̻����� ����
		r_X = f_X; //�̻��� ��ġ
		r_Y = f_Y;
	}
	else { //�̻����� �����ִ� ��Ȳ
		r_output = '!';
		r_Y -= 1;

		if (r_Y < 0) {
			r_state = 0; //�̻��� �ϳ��� �����
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

	//// 1.2. ��� �κ��� '.'���� ä���.
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			cout << "_";
		}
		cout << endl;
	}

	//// 1.3. ��� �Ʒ��� �ð��� ǥ���Ѵ�,
	//cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl;

	//�̻��� �׸���
	if (r_state != 0) {//���� �̻����� ���� ���¶��
		cur.X = r_X;
		cur.Y = r_Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
		cout << r_output;
		cout.flush();
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
			else if (event.key.keysym.sym == SDLK_SPACE) {//�����̽� ������ �̻��� ����
				r_state=1;
			}
			break;

		case SDL_KEYUP:
			f_state = 0;//up�ϸ� ����
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
void ClearGame()
{
}
