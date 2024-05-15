#define _CRT_SECURE_NO_WARNINGS
#include "GameStage.h"
#include <stack>
#define M_SIZE 5 //미사일 개수


//전투기 이미지
// <a href="https://kr.lovepik.com/images/png-macbook-air.html">Air Png vectors by Lovepik.com</a>
//미사일 효과음 : ✔ SFX provided by 셀바이뮤직
//https://sellbuymusic.com/md/sionnnz-ycbhnwh


using namespace std;

////미사일 발사 여부 판단 함수
//bool isGone(Missile* r_list) {
//    for (int i = 0; i < M_SIZE; i++) {
//        if (r_list[i].gone)
//            return true; //발사
//    }
//    return false; //미발사
//}

void Stage::UpdateScoreTexture()
{
    if (g_score_int != 0)
    {
        SDL_DestroyTexture(g_score_int);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        g_score_int = 0;
    }

    sprintf(text, u8"%d", r_state); // 문자열 포맷을 사용하여 text에 문자열을 생성합니다.

    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, text, { 255,255,255 });

    g_score_int_rect.x = screenWidth-50;
    g_score_int_rect.y = screenHeight-50;
    g_score_int_rect.w = 15;
    g_score_int_rect.h = 20;

    g_score_int = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

}


/////////////////////////////////////////////////////////////
// 초기화.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
Stage::Stage(){
    f_state = -1; //방향키 아무것도 안 눌림
    r_state = 5; //아직 안 나간 미사일 5개
    //f_head = 2; //방향이 위,,
    stop = true; //정지 상황으로 초기화
    button = false; //true가 되면 버튼 생성


    //모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }
  
    r_list = new Missile[M_SIZE]; //미사일 5개 세팅
    //r_state가 0번부터 가자
    r_push = false;
    //미사일 모두 off
    for (int i = 0;i < M_SIZE;i++) {
        r_list[i].gone = false;//그리지 않는 것으로 초기화
    }

    // BG 이미지 로드
    SDL_Surface* bg_surface = IMG_Load("../../Resources/background.jpg");
    g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);


    g_bg_destination_rect.x = 0;
    g_bg_destination_rect.y = 0;
    g_bg_destination_rect.w = screenWidth; //전체 영역에 그리기
    g_bg_destination_rect.h = screenHeight;

    //전투기 이미지 로드
    SDL_Surface* f_sheet_surface = IMG_Load("../../Resources/fighter.png");
    f_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, f_sheet_surface);
    SDL_FreeSurface(f_sheet_surface);//해제 필수

    f_source_rect.x = 0;
    f_source_rect.y = 0;
    f_source_rect.w = 1280;
    f_source_rect.h =1280;
    
    f_destination_rect.w = 150; //크기 150*150
    f_destination_rect.h = 150;
    f_X = (screenWidth / 2 - f_destination_rect.w/2); //중앙
    f_Y = (screenWidth / 2 - f_destination_rect.h/2); //중앙
    f_destination_rect.x = f_X; //그려질 좌표 지정 중앙에 그려진다
    f_destination_rect.y = f_Y;

    //미사일 이미지 로드
    SDL_Surface* r_sheet_surface = IMG_Load("../../Resources/bomb.png");
    r_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, r_sheet_surface);

    SDL_FreeSurface(r_sheet_surface);//해제 필수

    r_source_rect.x = 0;
    r_source_rect.y = 0;
    r_source_rect.w = 309;
    r_source_rect.h = 1096;

    r_destination_rect.x = 0; //기본 값 0,0 설정
    r_destination_rect.y = 0;
    r_destination_rect.w = 15; //크기 설정 대충 1:3비율
    r_destination_rect.h = 45;


    //음향 효과 가져오기
    // Set the music volume 
    Mix_VolumeMusic(128);

    // Load the wave and mp3 files 
    missile = Mix_LoadWAV("../../Resources/Laser.wav");
    if (missile == NULL)
    {
        printf("%s\n", Mix_GetError());
    }
    //버튼 음향 가져오기
    recharge = Mix_LoadWAV("../../Resources/recharge.wav");
    if (!recharge)
    {
        printf(" %s\n", Mix_GetError());
        // this might be a critical error...
    }

    //미사일 개수 텍스쳐설정
    UpdateScoreTexture();

    //버튼 위치 설정
    g_button_rect.x = g_score_int_rect.x - 130;
    g_button_rect.y = g_score_int_rect.y - 20;
    g_button_rect.w = 100;
    g_button_rect.h = 50;


    //폰트 열기
    fontK = TTF_OpenFont("../../Resources/Pretendard-Bold.ttf", 100);   
    //"재장착" 설정
    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"재충전", { 0,0,0 });

    g_score_kr_rect.x = g_button_rect.x+15;
    g_score_kr_rect.y = g_button_rect.y+10;
    g_score_kr_rect.w = 70;
    g_score_kr_rect.h = 30;
    g_score_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

 
    // std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
    setvbuf(stdout, NULL, _IOLBF, 4096);

}

void Stage::Reset() {
    //f_head = 2;
    f_state = -1; //방향키 안 눌린 걸로 초기화
    r_state = 5; //5로 설정
    stop = true;
    button = false;

    //방향키 모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }

    //미사일 모두 off
    /*for (int i = 0; i < M_SIZE; i++)
        r_list[i].gone = false;*/

    r_push = false;//미사일 키 안 눌림
    for (int i = 0;i < M_SIZE;i++) {
        r_list[i].gone = false;//그리지 않는 것으로 초기화
    }

    //위치 초기화
    f_X = (screenWidth / 2 - f_destination_rect.w / 2);
    f_Y = (screenWidth / 2 - f_destination_rect.h * 2);
    f_destination_rect.x = f_X; 
    f_destination_rect.y = f_Y ;


    UpdateScoreTexture();

}


/////////////////////////////////////////////////////////////
// Update() 
void Stage::Update() {
    if (!stop) {
        if (f_state == 0) { //좌측이동
            f_X -= 10;
        }
        else if (f_state == 1) {//우측이동
            f_X += 10;
        }
        else if (f_state == 2) {//위로 이동
            f_Y -= 10;
        }
        else if (f_state == 3) {//아래로 이동
            f_Y += 10;
        }
    }

    //비행기 범위 설정
    if (f_X > screenWidth) { //f_X > 75이면 실행 -> 비행기가 오른쪽 화면으로 나가면 실행
        f_X = 0 - f_destination_rect.w; //좌측 화면에서부터 보이게 설정
    }
    else if (f_X < 0 - f_destination_rect.w) {
        f_X = screenWidth;
    }
    if (f_Y > screenHeight) {
        f_Y = 0 - (f_destination_rect.h);
    }
    else if (f_Y < 0 - (f_destination_rect.h)) {
        f_Y = screenHeight;
    }


    //미사일 0개이면 button 활성화, 아니면 버튼 비활성화
    if (r_state == 0) {
        button = true;//button true
    }
    else
        button = false;


    //미사일 추가
   ////미사일 위치 저장 -> 비행기 좌표+(w/2)의 값을 할당하기
    if (r_push) {//미사일 버튼이 눌렸으면
        r_push = false;//일단 미사일 버튼 해제
        Mix_PlayChannel(5, missile, 0);//미사일 소리

        //r_state : 5,4,3,2,1 순서로 감소
    }

    //미사일 정보 할당
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) { // 미사일이 나가 있는 경우
            //cout << "인덱스 " << i << "번 미사일 갱신" << endl;
            // 미사일의 위치를 업데이트합니다.
            switch (r_list[i].to) {
            case 0: // 왼쪽 이동
                r_list[i].x -= 30;
                break;
            case 1: // 오른쪽 이동
                r_list[i].x += 30;
                break;
            case -1:
            case 2: // 위로 이동
                r_list[i].y -= 30;
                break;
            case 3: // 아래로 이동
                r_list[i].y += 30;
                break;
            }
        }
        else { // 미사일이 나가지 않은 경우
            // 비행기의 위치를 기반으로 미사일의 위치를 설정합니다.
            
            r_list[i].to = f_state;
            switch (f_state) {
            case 0://왼쪽
                r_list[i].x = f_X;
                r_list[i].y = f_Y + f_destination_rect.h / 2 - r_destination_rect.h / 2;
                break;
            case 1:
                r_list[i].x = f_X + f_destination_rect.w / 2;
                r_list[i].y = f_Y + f_destination_rect.h / 2 - r_destination_rect.h / 2;
                break;
            case -1:
            case 2:
                r_list[i].x = f_X + f_destination_rect.w / 2 - r_destination_rect.w / 2;
                r_list[i].y = f_Y;
                break;
            case 3:
                r_list[i].x = f_X + f_destination_rect.w / 2 - r_destination_rect.w / 2;
                r_list[i].y = f_Y + f_destination_rect.h / 2;
                break;
            }
        }
    }
    for (int i = 0;i < M_SIZE;i++) {
        //화면을 넘어간 미사일은 gone을 false로 바꾼다. ->  안 그릴 거임
        if (r_list[i].gone) {
            
            if (r_list[i].y < 0 || r_list[i].x < 0 || r_list[i].y >screenHeight+r_destination_rect.y || r_list[i].x >screenWidth+r_destination_rect.w) {
                //cout << "인덱스 " << i << "번 미사일 제거" << endl;
                r_list[i].gone = false;
            }
        }
    }

}

/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Stage::Render() {
    //// 1. 배경 그리기.
    // Background
    SDL_RenderCopy(g_renderer, g_bg_texture, NULL, &g_bg_destination_rect);

    UpdateScoreTexture();
    ////미사일 그리기
    for (int i = 0; i < M_SIZE; i++) {
        if (r_list[i].gone) {
            
            r_destination_rect.x = r_list[i].x;
            r_destination_rect.y = r_list[i].y;
            //cout << "인덱스 " << i << "번 미사일 그리기" << endl;
            switch (r_list[i].to) {
            case 0://좌
                SDL_RenderCopyEx(g_renderer, r_sheet_texture, &r_source_rect, &r_destination_rect, -90, NULL, SDL_FLIP_NONE);
                break;
            case 1://우
                SDL_RenderCopyEx(g_renderer, r_sheet_texture, &r_source_rect, &r_destination_rect, 90, NULL, SDL_FLIP_NONE);
                break;
            case -1:
            case 2://위
                SDL_RenderCopyEx(g_renderer, r_sheet_texture, &r_source_rect, &r_destination_rect, 0, NULL, SDL_FLIP_NONE);
                break;
            case 3://아래
                SDL_RenderCopyEx(g_renderer, r_sheet_texture, &r_source_rect, &r_destination_rect, 180, NULL, SDL_FLIP_NONE);
                break;
            default:
                break;
            }
        }
    }
    

    //전투기 그리기
    f_destination_rect.x = f_X;
    f_destination_rect.y = f_Y;
    
    
    switch (f_state) {//
    
    case 0://좌
        SDL_RenderCopyEx(g_renderer, f_sheet_texture, &f_source_rect, &f_destination_rect, -90, NULL, SDL_FLIP_NONE);
        break;
    case 1://우
        SDL_RenderCopyEx(g_renderer, f_sheet_texture, &f_source_rect, &f_destination_rect, 90, NULL, SDL_FLIP_NONE);
        break;
    case -1:
    case 2://위
        SDL_RenderCopyEx(g_renderer, f_sheet_texture, &f_source_rect, &f_destination_rect, 0, NULL, SDL_FLIP_NONE);
        break;
    case 3://아래
        SDL_RenderCopyEx(g_renderer, f_sheet_texture, &f_source_rect, &f_destination_rect, 180, NULL, SDL_FLIP_NONE);
        break;
    default:
        break;
    }

    //버튼이 true면 버튼 그림
    if(button)
    {
        SDL_SetRenderDrawColor(g_renderer, 255, 192, 203, 0);
        SDL_RenderFillRect(g_renderer, &g_button_rect);
        SDL_RenderCopy(g_renderer, g_score_kr, 0, &g_score_kr_rect);
        
    }
    
    SDL_RenderCopy(g_renderer, g_score_int, 0, &g_score_int_rect);

    SDL_RenderPresent(g_renderer);
}

/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Stage:: HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = 0; //현재 눌린 값이 LEFT
                f_list[f_state] = true;
                stop = false;
                
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = 1;
                f_list[f_state] = true;
                stop = false;
                
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = 2;
                f_list[f_state] = true;
                stop = false;

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = 3;
                f_list[f_state] = true;
                stop = false;

            }

            else if (event.key.keysym.sym == SDLK_SPACE) {//스페이스 누르면 미사일 나감
                if (r_state > 0) {
                    r_push = true;
                    for (int i = 0; i < M_SIZE; i++) {
                        if (!r_list[i].gone) { // 발사되지 않은 미사일을 찾아서 발사
                            r_list[i].gone = true;
                            r_state--;
                            break;
                        }
                    }
                }
            }
            break;

        case SDL_KEYUP:
          
            if (event.key.keysym.sym == SDLK_LEFT) {
                f_list[0] = false;
                
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_list[1] = false;
                
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_list[2] = false;
                
            } 
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_list[3] = false;
                
            }
            

            //만약 up되지 않은 놈들이 있다면
            if (f_list[0])
                f_state = 0;
            if (f_list[1])
                f_state = 1;
            if (f_list[2])
                f_state = 2;
            if (f_list[3])
                f_state = 3;

            if (f_list[0]!=true&& f_list[1]!=true && f_list[2]!=true && f_list[3]!=true)
                stop = true;

            break;

        case SDL_MOUSEBUTTONDOWN:

            //마우스 우클릭이면 엔딩 화면으로
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                
                g_current_game_phase = PHASE_ENDING;

            }

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (button) {//버튼이 켜져있으면 버튼을 누르는 순간

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= g_button_rect.x && mouse_x <= g_button_rect.x + g_button_rect.w &&
                        mouse_y >= g_button_rect.y && mouse_y <= g_button_rect.y + g_button_rect.h
                        )
                    {
                        Mix_PlayChannel(-1, recharge, 0);//효과음 출력
                        button = false;//버튼이 false로 변하는 순간 미사일이 재충전
                        r_state = 5; //미사일 재충전

                    }
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
Stage::~Stage() {
    SDL_DestroyTexture(f_sheet_texture);
    SDL_DestroyTexture(r_sheet_texture);
    SDL_DestroyTexture(g_bg_texture);

    
    if (missile) Mix_FreeChunk(missile);
    if (recharge) Mix_FreeChunk(recharge);

    TTF_CloseFont(fontK);

    delete[] r_list;
}
