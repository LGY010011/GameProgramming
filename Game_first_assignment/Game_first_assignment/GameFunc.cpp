#define _CRT_SECURE_NO_WARNINGS
#include "GameFunc.h"
#include <windows.h>
#include "SDL_image.h"

#define M_SIZE 5 //미사일 개수

using namespace std;

int screenWidth, screenHeight;


//미사일 구조체
typedef struct Missile {
    int x, y; //좌표
    bool gone; //발사여부
} Missile;



bool f_list[4];
int f_state; //현재 누른 키의 인덱스값

int r_state;
string r_output;

Missile* r_list = new Missile[M_SIZE];

int countF; //현재 눌려있는 키의 개수 카운트

int f_X;
int f_Y;

int score;//점수


// 흘러간 시간 기록
//double g_elapsed_time_ms;

//전투기 이미지 변수
SDL_Texture* f_sheet_texture; //붙일 이미지 텍스쳐 저장소
SDL_Rect f_destination_rect; // x,y,w,h

//미사일 이미지 변수
SDL_Rect r_destination_rect;
SDL_Texture* r_sheet_texture;

//배경 이미지 변수
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

//음향 변수들
Mix_Chunk* missile;
Mix_Music* background_music;

//폰트 변수
TTF_Font* fontK;
SDL_Texture* g_score_kr;
SDL_Rect g_score_kr_rect;

SDL_Texture* g_score_int;
SDL_Rect g_score_int_rect;
char text[10]; // 적당한 크기의 문자열 버퍼를 할당합니다.


//미사일 발사 여부 판단 함수
bool isGone(Missile* r_list) {
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone)
            return true; //발사
    }
    return false; //미발사
}


void UpdateScoreTexture()
{
    if (g_score_int != 0)
    {
        SDL_DestroyTexture(g_score_int);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        g_score_int = 0;
    }

    sprintf(text, u8"%05d", score); // 문자열 포맷을 사용하여 text에 문자열을 생성합니다.

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
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {
    f_state = 4; //stop으로 초기화
    r_state = 0; //0은 발사 안 함 , 5이면 다 나감

    g_flag_running = true;

    //모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }
    countF = 0;

    f_X = 25;
    f_Y = 50;

    score = 0;//점수 초기화

    //미사일 모두 off
    for (int i = 0; i < M_SIZE; i++)
        r_list[i].gone = false;

    //g_elapsed_time_ms = 0;


    //전투기 이미지 로드
    SDL_Surface* f_sheet_surface = IMG_Load("../../Resources/fighter.png");
    f_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, f_sheet_surface);
    SDL_FreeSurface(f_sheet_surface);//해제 필수

    f_destination_rect.x = f_X * 10; //그려질 좌표 지정 (150,180)에 그려진다
    f_destination_rect.y = f_Y * 10;
    f_destination_rect.w = 150; //200x200 크기로 설정
    f_destination_rect.h = 150;

    //미사일 이미지 로드
    SDL_Surface* r_sheet_surface = IMG_Load("../../Resources/bomb.png");
    r_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, r_sheet_surface);
    SDL_FreeSurface(r_sheet_surface);//해제 필수

    r_destination_rect.x = 0; //기본 값 0,0 설정
    r_destination_rect.y = 0;
    r_destination_rect.w = 15; //크기 설정 대충 1:3비율
    r_destination_rect.h = 45;

    // BG 이미지 로드
    SDL_Surface* bg_surface = IMG_Load("../../Resources/mountains.png");
    g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);

    g_bg_destination_rect.x = 0;
    g_bg_destination_rect.y = 0;
    g_bg_destination_rect.w = screenWidth; //전체 영역에 그리기
    g_bg_destination_rect.h = screenHeight;

    //음향 효과 가져오기
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
    Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작

    //폰트 열기
    fontK = TTF_OpenFont("../../Resources/Pretendard-Bold.ttf", 100);
    //"점수" 설정
    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"점수 : ", { 255,255,255 });

    g_score_kr_rect.x = 0;
    g_score_kr_rect.y = 0;
    g_score_kr_rect.w = 50;
    g_score_kr_rect.h = 25;
    g_score_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    UpdateScoreTexture();



    // std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
    setvbuf(stdout, NULL, _IOLBF, 4096);

}



/////////////////////////////////////////////////////////////
// Update() 
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
    if (f_X > screenWidth / 10) { //f_X > 75이면 실행 -> 비행기가 오른쪽 화면으로 나가면 실행
        f_X = 0 - (f_destination_rect.w / 10); //좌측 화면에서부터 보이게 설정
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

    ////미사일 위치 저장 -> 비행기 좌표+(w/2)의 값을 할당하기
    // 모든 미사일 위치 업데이트
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) // 발사된 미사일인 경우
            r_list[i].y--; // 미사일을 위로 이동
        else { //나가있지 않은 미사일이면 좌표값 할당
            r_list[i].x = f_X + (f_destination_rect.w / 10) / 2 - 0.2;
            r_list[i].y = f_Y;
        }

    }

    // 화면을 벗어난 미사일 제거
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone && r_list[i].y < 0) {
            r_list[i].gone = false; // 미사일 제거
            r_state--; // 발사된 미사일 개수 감소
        }
    }

    //g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {
    //// 1. 배경 그리기.
    // Background
    SDL_RenderCopy(g_renderer, g_bg_texture, NULL, &g_bg_destination_rect);

    ////미사일 그리기
    if (isGone(r_list)) {//만약 미사일이 나간 상태라면
        for (int i = 0; i < M_SIZE; i++) {
            if (r_list[i].gone) { //나가있는 미사일이라면 그리기
                r_destination_rect.x = r_list[i].x * 10;
                r_destination_rect.y = r_list[i].y * 10;
                SDL_RenderCopy(g_renderer, r_sheet_texture, NULL, &r_destination_rect);
            }
        }

    }

    SDL_RenderCopy(g_renderer, g_score_kr, 0, &g_score_kr_rect);


    SDL_RenderCopy(g_renderer, g_score_int, 0, &g_score_int_rect);

    //전투기 그리기
    f_destination_rect.x = f_X * 10;
    f_destination_rect.y = f_Y * 10;
    SDL_RenderCopy(g_renderer, f_sheet_texture, NULL, &f_destination_rect);


    SDL_RenderPresent(g_renderer);
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

            else if (event.key.keysym.sym == SDLK_SPACE) {//스페이스 누르면 미사일 나감
                if (r_state < M_SIZE) { // 최대 미사일 개수보다 작을 때만 발사 가능하도록 수정
                    score += 10;
                    UpdateScoreTexture();
                    for (int i = 0; i < M_SIZE; i++) {
                        if (!r_list[i].gone) { // 발사되지 않은 미사일을 찾아서 발사
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
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame() {
    SDL_DestroyTexture(f_sheet_texture);
    SDL_DestroyTexture(r_sheet_texture);
    SDL_DestroyTexture(g_bg_texture);

    if (background_music) Mix_FreeMusic(background_music);
    if (missile) Mix_FreeChunk(missile);

    TTF_CloseFont(fontK);

    delete[] r_list;
}
