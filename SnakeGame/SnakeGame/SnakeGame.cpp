#define _CRT_SECURE_NO_WARNINGS
#include "SnakeGame.h"


void SnakeGame::UpdateScoreTexture()
{
    if (snake_length != 0)
    {
        SDL_DestroyTexture(snake_length);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        snake_length = 0;
    }

    sprintf(text, u8"%03d", snake->getSnakeLength()); // 문자열 포맷을 사용하여 text에 문자열을 생성합니다.

    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, text, { 255,255,255 });

    snake_length_rect.x = screenWidth-GRID*3;
    snake_length_rect.y = GRID*4;
    snake_length_rect.w = GRID*2;
    snake_length_rect.h = GRID;

    snake_length = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

}

void SnakeGame::UpdateTimeTexture(int ms)
{
    if (text_time != 0)
    {
        SDL_DestroyTexture(text_time);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        text_time = 0;
    }

    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    char timeStr[6];
    sprintf(timeStr, "%02d:%02d", minutes, seconds);

    SDL_Surface* tmp_surface = TTF_RenderText_Blended(fontK, timeStr, { 255,255,255 });
    text_time_rect.x = screenWidth - GRID * 3 - GRID / 2;
    text_time_rect.y = screenHeight - GRID * 3;
    text_time_rect.w = GRID * 3;
    text_time_rect.h = GRID * 2;

    text_time = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

    SDL_FreeSurface(tmp_surface);
}


SnakeGame::SnakeGame() {
    std::cout << "게임 생성" << std::endl;
    g_flag_running = true;
    //2. 텍스쳐 불러오기
    //2.1 Snake 텍스쳐 불러오기
    snake = new Snake();

    SDL_Surface* snakeHead_sheet_surface = IMG_Load("../../Resources/head.png");
    std::cout << "snake 헤드 이미지 로드" << std::endl;
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, snakeHead_sheet_surface);
    SDL_FreeSurface(snakeHead_sheet_surface);//해제 필수
    snakeHead_source_rect.x = 0;
    snakeHead_source_rect.y = 0;
    snakeHead_source_rect.w = 512;
    snakeHead_source_rect.h = 512;


    snake_destination_rect.w = GRID; //크기 10*10
    snake_destination_rect.h = GRID;

    snake_destination_rect.x = snake->getSnakeHead()->x; //화면 중앙에 그려질 것
    snake_destination_rect.y = snake->getSnakeHead()->y;


    SDL_Surface* snake_sheet_surface = IMG_Load("../../Resources/snake.png");
    std::cout << "snake 이미지 로드" << std::endl;
    snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_sheet_surface);
    SDL_FreeSurface(snake_sheet_surface);//해제 필수

    snake_source_rect.x = 0;
    snake_source_rect.y = 0;
    snake_source_rect.w = 512;
    snake_source_rect.h = 512;

 
    
    //2.2 아이템 텍스쳐 불러오기
    item = new Item(snake->getSnakeList());

    SDL_Surface* item_sheet_surface = IMG_Load("../../Resources/item.png");
    std::cout << "아이템 이미지 로드" << std::endl;

    item_texture = SDL_CreateTextureFromSurface(g_renderer, item_sheet_surface);
    SDL_FreeSurface(item_sheet_surface);//해제 필수

    item_source_rect.x = 0;
    item_source_rect.y = 0;
    item_source_rect.w = 512;
    item_source_rect.h = 512;

    item_destination_rect.w = GRID; //크기 10*10
    item_destination_rect.h = GRID;
    item_destination_rect.x = item->getX(); //그려질 좌표 지정
    item_destination_rect.y = item->getY();

    

    //2.3 background 텍스쳐 불러오기
    //배경 이미지 변수
    SDL_Surface* bg_sheet_surface = IMG_Load("../../Resources/background.png");
    std::cout << "배경 이미지 로드" << std::endl;
    bg_texture= SDL_CreateTextureFromSurface(g_renderer, bg_sheet_surface);
    SDL_FreeSurface(bg_sheet_surface);//해제 필수
    bg_destination_rect.x = GRID;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth-GRID*5;
    bg_destination_rect.h = screenHeight-GRID*2;
    
    //3. 폰트 가져오기
    //폰트 소스 호출
    fontK=TTF_OpenFont("../../Resources/establish Retrosans.ttf", 100);
    //3.1 ready 텍스쳐 만들기
    SDL_Surface * tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Ready", {0,0,0});
    read_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2;
    read_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    read_rect.w = tmp_surface->w;
    read_rect.h = tmp_surface->h;
    ready = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.2 game over 텍스쳐 만들기
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Game Over", { 0,0,0 });
    over_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2+bg_destination_rect.x;
    over_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    over_rect.w = tmp_surface->w;
    over_rect.h = tmp_surface->h;
    over = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.3 score 텍스쳐
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"SCORE", { 255,255,255 });
    snake_score_rect.x = screenWidth - GRID * 3 - GRID / 2;
    snake_score_rect.y = GRID;
    snake_score_rect.w = GRID*3;
    snake_score_rect.h = GRID*2;
    snake_score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.4 뱀 길이 숫자 출력 텍스쳐
    UpdateScoreTexture();
    

    //3. 조작키 초기화
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//방향키 안 누름
    //4. 시간 초기화
    time_ms_ = 0;
    UpdateTimeTexture(time_ms_);
    
}

void SnakeGame::Render() {
    //std::cout << "render" << std::endl;
    //// 1. 배경 그리기.
    SDL_RenderClear(g_renderer); //검정으로 초기화
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);

    //// 2. 아이템 그리기
    item_destination_rect.x = item->getX(); //그려질 좌표 지정
    item_destination_rect.y = item->getY();
    SDL_RenderCopy(g_renderer, item_texture, NULL, &item_destination_rect);
    
    //// 3. 뱀 그리기
    auto snakeList = snake->getSnakeList();
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->x; // 그려질 좌표 지정
        snake_destination_rect.y = (*it)->y;

        // 뱀의 헤드 노드인 경우에는 헤드 이미지를 사용하고, 그렇지 않은 경우에는 기존의 뱀 이미지를 사용합니다.
        if (it == snakeList.begin()) {

            switch (s_state) {
            case 0://좌
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, -90, NULL, SDL_FLIP_NONE);
                break;
            case 1://우
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 90, NULL, SDL_FLIP_NONE);
                break;
            case -1:
            case 2://위
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 0, NULL, SDL_FLIP_NONE);
                break;
            case 3://아래
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 180, NULL, SDL_FLIP_NONE);
                break;
            default:
                break;
            }
            //SDL_RenderCopy(g_renderer, snakeHead_texture, NULL, &snake_destination_rect);
        }
        else {
            SDL_RenderCopy(g_renderer, snake_texture, NULL, &snake_destination_rect);
        }
    }

    
    //점수 텍스쳐
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, snake_score, NULL, &snake_score_rect);
    SDL_RenderCopy(g_renderer, snake_length, NULL, &snake_length_rect);

    if (snakeGame_running == 0) {
        SDL_RenderCopy(g_renderer, ready, NULL, &read_rect);
    }else if(snakeGame_running == 2) {
        SDL_RenderCopy(g_renderer, over, NULL, &over_rect);
    }
    
    UpdateTimeTexture(time_ms_);
    SDL_RenderCopy(g_renderer, text_time, NULL, &text_time_rect);

    SDL_RenderPresent(g_renderer);
}

void SnakeGame::Update() {
    //std::cout << "update" << std::endl;
    if (snakeGame_running == 0 || snakeGame_running==2) // 아직 방향키가 안 눌린 상황이라면 업데이트 안 함
        return;
    //1. snake & item 업데이트
    snake->setDirection(s_state); 
    
    
    //1.1 snake가 item과 충돌했다면
    if (snake->isCollidingItem(item,s_state)) {
        snake->eatItem(item->getItemPower());//길이 증가
        item->spawn(snake->getSnakeList()); //item 위치 리스폰
    }
    //1.2 snake가 자신의 몸과 충돌했다면
    if (snake->isCollidingSelf(s_state))
        snakeGame_running = 2;
    //1.3 snake가 벽과 충돌했다면
    if (snake->isColldingWall(s_state))
        snakeGame_running = 2;

    if (snakeGame_running != 2)
        snake->move();
    //시간 업데이트
    static Uint32 last_ticks = SDL_GetTicks(); // !중요! static 으로 선언한 이유 확일 할 것.
    Uint32 current_ticks = SDL_GetTicks();

    time_ms_ += current_ticks - last_ticks;
    UpdateTimeTexture(time_ms_);	// 업데이트 된 시간(time_ms_)을 문자로 변환한 후 texture로 만든다.
    

    last_ticks = current_ticks;
}

void SnakeGame::HandleEvents() {
    //std::cout << "handleEvents" << std::endl;
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (snakeGame_running == 2)
                break;
            //방향키 누르는 순간 정지가 풀리며 계속 이동
            if (event.key.keysym.sym == SDLK_LEFT) {
                s_state = 0; //현재 눌린 값이 LEFT
                stop = false;
                if(snakeGame_running==0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                s_state = 1;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                s_state = 2;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                s_state = 3;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (snakeGame_running == 2) {
                    Reset();
                }
                break;
            }
        }
    }
}

void SnakeGame::Reset() {
    //조작키 초기화
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//방향키 안 누름

    //뱀 객체 삭제 했다가 재생성
    delete snake;
    snake = new Snake();
    //item 재배치
    item->spawn(snake->getSnakeList());
    UpdateScoreTexture();

    //time 초기화
    time_ms_ = 0;
    UpdateTimeTexture(time_ms_);
}


SnakeGame::~SnakeGame() {
    //이미지 텍스쳐 해제
    SDL_DestroyTexture(item_texture);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(bg_texture);
    //폰트 텍스쳐 해제
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(snake_length);
    SDL_DestroyTexture(snake_score);
    SDL_DestroyTexture(text_time);

}
