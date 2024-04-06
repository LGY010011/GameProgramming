#define _CRT_SECURE_NO_WARNINGS
#include "GameFunc.h"
#include <windows.h>
#include "SDL_image.h"

#define M_SIZE 5 //�̻��� ����

using namespace std;

int screenWidth, screenHeight;


//�̻��� ����ü
typedef struct Missile {
    int x, y; //��ǥ
    bool gone; //�߻翩��
} Missile;



bool f_list[4];
int f_state; //���� ���� Ű�� �ε�����

int r_state;
string r_output;

Missile* r_list = new Missile[M_SIZE];

int countF; //���� �����ִ� Ű�� ���� ī��Ʈ

int f_X;
int f_Y;

int score;//����


// �귯�� �ð� ���
//double g_elapsed_time_ms;

//������ �̹��� ����
SDL_Texture* f_sheet_texture; //���� �̹��� �ؽ��� �����
SDL_Rect f_destination_rect; // x,y,w,h

//�̻��� �̹��� ����
SDL_Rect r_destination_rect;
SDL_Texture* r_sheet_texture;

//��� �̹��� ����
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

//���� ������
Mix_Chunk* missile;
Mix_Music* background_music;

//��Ʈ ����
TTF_Font* fontK;
SDL_Texture* g_score_kr;
SDL_Rect g_score_kr_rect;

SDL_Texture* g_score_int;
SDL_Rect g_score_int_rect;
char text[10]; // ������ ũ���� ���ڿ� ���۸� �Ҵ��մϴ�.


//�̻��� �߻� ���� �Ǵ� �Լ�
bool isGone(Missile* r_list) {
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone)
            return true; //�߻�
    }
    return false; //�̹߻�
}


void UpdateScoreTexture()
{
    if (g_score_int != 0)
    {
        SDL_DestroyTexture(g_score_int);		// !!!�߿�!!!  �̹� �����Ǿ��ִ� texture �� ������ �ݵ�� �޸𸮿��� �������Ѵ�. !!!
        g_score_int = 0;
    }

    sprintf(text, u8"%05d", score); // ���ڿ� ������ ����Ͽ� text�� ���ڿ��� �����մϴ�.

    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, text, { 255,255,255 });

    g_score_int_rect.x = 50;
    g_score_int_rect.y = 0;
    g_score_int_rect.w = 50;
    g_score_int_rect.h = 25;

    g_score_int = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);


}

/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {
    f_state = 4; //stop���� �ʱ�ȭ
    r_state = 0; //0�� �߻� �� �� , 5�̸� �� ����

    g_flag_running = true;

    //��� �� ���� ������ �ʱ�ȭ -> stop
    for (int i = 0; i < f_state; i++) {//0�� ����, ...
        f_list[i] = false;
    }
    countF = 0;

    f_X = 25;
    f_Y = 50;

    score = 0;//���� �ʱ�ȭ

    //�̻��� ��� off
    for (int i = 0; i < M_SIZE; i++)
        r_list[i].gone = false;

    //g_elapsed_time_ms = 0;


    //������ �̹��� �ε�
    SDL_Surface* f_sheet_surface = IMG_Load("../../Resources/fighter.png");
    f_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, f_sheet_surface);
    SDL_FreeSurface(f_sheet_surface);//���� �ʼ�

    f_destination_rect.x = f_X * 10; //�׷��� ��ǥ ���� (150,180)�� �׷�����
    f_destination_rect.y = f_Y * 10;
    f_destination_rect.w = 150; //200x200 ũ��� ����
    f_destination_rect.h = 150;

    //�̻��� �̹��� �ε�
    SDL_Surface* r_sheet_surface = IMG_Load("../../Resources/bomb.png");
    r_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, r_sheet_surface);
    SDL_FreeSurface(r_sheet_surface);//���� �ʼ�

    r_destination_rect.x = 0; //�⺻ �� 0,0 ����
    r_destination_rect.y = 0;
    r_destination_rect.w = 15; //ũ�� ���� ���� 1:3����
    r_destination_rect.h = 45;

    // BG �̹��� �ε�
    SDL_Surface* bg_surface = IMG_Load("../../Resources/mountains.png");
    g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);

    g_bg_destination_rect.x = 0;
    g_bg_destination_rect.y = 0;
    g_bg_destination_rect.w = screenWidth; //��ü ������ �׸���
    g_bg_destination_rect.h = screenHeight;

    //���� ȿ�� ��������
    // Set the music volume 
    Mix_VolumeMusic(128);

    // Load the wave and mp3 files 
    missile = Mix_LoadWAV("../../Resources/Laser.wav");
    if (missile == NULL)
    {
        printf("%s\n", Mix_GetError());
    }

    background_music = Mix_LoadMUS("../../Resources/backgroundMs.mp3");
    if (!background_music)
    {
        printf(" %s\n", Mix_GetError());
        // this might be a critical error...
    }
    //Mix_PlayMusic(background_music, -1);
    Mix_FadeInMusic(background_music, -1, 2000);//�뷡 ���̵������� �ٷ� ����

    //��Ʈ ����
    fontK = TTF_OpenFont("../../Resources/Pretendard-Bold.ttf", 100);
    //"����" ����
    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"���� : ", { 255,255,255 });

    g_score_kr_rect.x = 0;
    g_score_kr_rect.y = 0;
    g_score_kr_rect.w = 50;
    g_score_kr_rect.h = 25;
    g_score_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    UpdateScoreTexture();



    // std::cout ��¿� ���۸� ����Ͽ�, ��� �ӵ��� �������� ������ ���Ѵ�.
    setvbuf(stdout, NULL, _IOLBF, 4096);

}



/////////////////////////////////////////////////////////////
// Update() 
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
    if (f_X > screenWidth / 10) { //f_X > 75�̸� ���� -> ����Ⱑ ������ ȭ������ ������ ����
        f_X = 0 - (f_destination_rect.w / 10); //���� ȭ�鿡������ ���̰� ����
    }
    else if (f_X < 0 - (f_destination_rect.w / 10)) {
        f_X = screenWidth / 10;
    }
    if (f_Y > screenHeight / 10) {
        f_Y = 0 - (f_destination_rect.h / 10);
    }
    else if (f_Y < 0 - (f_destination_rect.h / 10)) {
        f_Y = screenHeight / 10;
    }

    ////�̻��� ��ġ ���� -> ����� ��ǥ+(w/2)�� ���� �Ҵ��ϱ�
    // ��� �̻��� ��ġ ������Ʈ
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) // �߻�� �̻����� ���
            r_list[i].y--; // �̻����� ���� �̵�
        else { //�������� ���� �̻����̸� ��ǥ�� �Ҵ�
            r_list[i].x = f_X + (f_destination_rect.w / 10) / 2 - 0.2;
            r_list[i].y = f_Y;
        }

    }

    // ȭ���� ��� �̻��� ����
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone && r_list[i].y < 0) {
            r_list[i].gone = false; // �̻��� ����
            r_state--; // �߻�� �̻��� ���� ����
        }
    }

    //g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {
    //// 1. ��� �׸���.
    // Background
    SDL_RenderCopy(g_renderer, g_bg_texture, NULL, &g_bg_destination_rect);

    ////�̻��� �׸���
    if (isGone(r_list)) {//���� �̻����� ���� ���¶��
        for (int i = 0; i < M_SIZE; i++) {
            if (r_list[i].gone) { //�����ִ� �̻����̶�� �׸���
                r_destination_rect.x = r_list[i].x * 10;
                r_destination_rect.y = r_list[i].y * 10;
                SDL_RenderCopy(g_renderer, r_sheet_texture, NULL, &r_destination_rect);
            }
        }

    }

    SDL_RenderCopy(g_renderer, g_score_kr, 0, &g_score_kr_rect);


    SDL_RenderCopy(g_renderer, g_score_int, 0, &g_score_int_rect);

    //������ �׸���
    f_destination_rect.x = f_X * 10;
    f_destination_rect.y = f_Y * 10;
    SDL_RenderCopy(g_renderer, f_sheet_texture, NULL, &f_destination_rect);


    SDL_RenderPresent(g_renderer);
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

            else if (event.key.keysym.sym == SDLK_SPACE) {//�����̽� ������ �̻��� ����
                if (r_state < M_SIZE) { // �ִ� �̻��� �������� ���� ���� �߻� �����ϵ��� ����
                    score += 10;
                    UpdateScoreTexture();
                    for (int i = 0; i < M_SIZE; i++) {
                        if (!r_list[i].gone) { // �߻���� ���� �̻����� ã�Ƽ� �߻�
                            Mix_PlayChannel(-1, missile, 0);
                            r_list[i].gone = true;
                            r_state++;
                            break;
                        }
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
    SDL_DestroyTexture(f_sheet_texture);
    SDL_DestroyTexture(r_sheet_texture);
    SDL_DestroyTexture(g_bg_texture);

    if (background_music) Mix_FreeMusic(background_music);
    if (missile) Mix_FreeChunk(missile);

    TTF_CloseFont(fontK);

    delete[] r_list;
}
