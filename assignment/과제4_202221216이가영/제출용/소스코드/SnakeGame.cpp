#define _CRT_SECURE_NO_WARNINGS
#include "SnakeGame.h"


extern int DASH_SPEED; // 대쉬 속도
extern int NORMAL_SPEED; // 일반 속도
extern Uint32 move_interval; // 뱀이 움직이는 간격


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
    g_flag_running = true;
    
    //2. 텍스쳐 불러오기
    //2.1 Snake 텍스쳐 불러오기
    snake = new Snake();

    SDL_Surface* snakeHead_sheet_surface = IMG_Load("../../Resources/head.png");
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
    snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_sheet_surface);
    SDL_FreeSurface(snake_sheet_surface);//해제 필수

    snake_source_rect.x = 0;
    snake_source_rect.y = 0;
    snake_source_rect.w = 512;
    snake_source_rect.h = 512;

    //2.2 아이템 텍스쳐 불러오기
    item = new Item(snake->getSnakeList());

    SDL_Surface* item_sheet_surface = IMG_Load("../../Resources/item.png");

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

    //2.3 monster 텍스쳐 불러오기
    // 몬스터 객체 생성
    for(int i = 0; i < 2; i++)
        monsterList.push_back(new Monster(snake->getSnakeList()));
    
    
    SDL_Surface* monster_sheet_surface = IMG_Load("../../Resources/monster.png");
    monster_texture = SDL_CreateTextureFromSurface(g_renderer, monster_sheet_surface);
    SDL_FreeSurface(monster_sheet_surface);//해제 필수

    monster_destination_rect.w = GRID; //크기 10*10
    monster_destination_rect.h = GRID;
    

    //2.3 background 텍스쳐 불러오기
    //배경 이미지 변수
    SDL_Surface* bg_sheet_surface = IMG_Load("../../Resources/background.png");
    bg_texture= SDL_CreateTextureFromSurface(g_renderer, bg_sheet_surface);
    SDL_FreeSurface(bg_sheet_surface);//해제 필수
    bg_destination_rect.x = GRID;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth-GRID*5;
    bg_destination_rect.h = screenHeight-GRID*2;
    
    //2.4 일시정지 텍스쳐 가져오기
    SDL_Surface* stop_sheet_surface = IMG_Load("../../Resources/stop.png");
    stop_texture = SDL_CreateTextureFromSurface(g_renderer, stop_sheet_surface);
    SDL_FreeSurface(stop_sheet_surface);//해제 필수

    stop_destination_rect.w = GRID * 10; //크기 10*10
    stop_destination_rect.h = GRID * 10;
    stop_destination_rect.x = (GRID + bg_destination_rect.w - stop_destination_rect.w) / 2;
    stop_destination_rect.y = (GRID + bg_destination_rect.h - stop_destination_rect.h) / 2;
    
    
    //3. 폰트 가져오기
    //폰트 소스 호출
    fontK=TTF_OpenFont("../../Resources/establish Retrosans.ttf", 100);
    //3.1 ready 텍스쳐 만들기
    SDL_Surface * tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Ready", {255, 255, 255});
    read_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2;
    read_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    read_rect.w = tmp_surface->w;
    read_rect.h = tmp_surface->h;
    ready = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    
    //3.2 readme 텍스쳐
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8">> 시작하려면 방향키를 누르세요", { 80, 80,80 });
    readme_rect.x = read_rect.x+GRID;
    readme_rect.y = read_rect.y + GRID*7;
    readme_rect.w = tmp_surface->w /5;
    readme_rect.h = tmp_surface->h/5+2;
    readme = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.3 game over 텍스쳐 만들기
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Game Over", { 0,0,0 });
    over_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2+bg_destination_rect.x;
    over_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    over_rect.w = tmp_surface->w;
    over_rect.h = tmp_surface->h;
    over = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.4 score 텍스쳐
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"SCORE", { 255,255,255 });
    snake_score_rect.x = screenWidth - GRID * 3 - GRID / 2;
    snake_score_rect.y = GRID;
    snake_score_rect.w = GRID*3;
    snake_score_rect.h = GRID*2;
    snake_score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.5 뱀 길이 숫자 출력 텍스쳐
    UpdateScoreTexture();
    

    //3. 조작키 초기화
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//방향키 안 누름
    //4. 시간 초기화
    time_ms_ = 0;
    //UpdateTimeTexture(time_ms_);
    SDL_SetTextureBlendMode(bg_texture, SDL_BLENDMODE_BLEND);
    monsterCollisionTime = 0;
    //lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
    
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
    
    //// 몬스터 그리기
    for(auto& monster : monsterList){
		monster_destination_rect.x = monster->getX(); // 그려질 좌표 지정
		monster_destination_rect.y = monster->getY();
		SDL_RenderCopy(g_renderer, monster_texture, NULL, &monster_destination_rect);
	}
    

    //// 3. 뱀 그리기
    //충돌 여부로 색상 설정
    // 뱀이 몬스터와 충돌했을 경우 뱀을 흰색으로 그립니다.

    auto snakeList = snake->getSnakeList();
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->x; // 그려질 좌표 지정
        snake_destination_rect.y = (*it)->y;

        // 뱀의 헤드 노드인 경우에는 헤드 이미지를 사용하고, 그렇지 않은 경우에는 기존의 뱀 이미지를 사용합니다.
        if (it == snakeList.begin()) {
            int angle = 0;
            switch (s_state) {
            case 0://좌
                angle = -90;
                break;
            case 1://우
                angle = 90;
                break;
            case -1:
            case 2://위
                angle = 0;
                break;
            case 3://아래
                angle = 180;
                break;
            default:
                break;
            }

            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            
            SDL_RenderCopy(g_renderer, snake_texture, NULL, &snake_destination_rect);
        }
    }
    //색상 복구
    SDL_SetTextureColorMod(snakeHead_texture, 255, 255, 255);
    SDL_SetTextureColorMod(snake_texture, 255, 255, 255);

    if (snakeGame_running != 1) {
        SDL_SetTextureAlphaMod(bg_texture, 127); // 50% 불투명도
        SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);
        SDL_SetTextureAlphaMod(bg_texture, 255);
    }
    
    //점수 텍스쳐
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, snake_score, NULL, &snake_score_rect);
    SDL_RenderCopy(g_renderer, snake_length, NULL, &snake_length_rect);

    if (snakeGame_running == 0) {
        SDL_RenderCopy(g_renderer, ready, NULL, &read_rect);
        SDL_RenderCopy(g_renderer, readme, NULL, &readme_rect);
    }else if(snakeGame_running == 2) {
        SDL_RenderCopy(g_renderer, over, NULL, &over_rect);
    }
    else if (snakeGame_running==3) {
        SDL_RenderCopy(g_renderer, stop_texture, NULL, &stop_destination_rect);
    }
    
    
    UpdateTimeTexture(time_ms_);
    SDL_RenderCopy(g_renderer, text_time, NULL, &text_time_rect);
    

    SDL_RenderPresent(g_renderer);
}

void SnakeGame::Update() {
    //std::cout << "update" << std::endl;
    if (snakeGame_running == 0 || snakeGame_running==2 || snakeGame_running == 3) // 아직 방향키가 안 눌린 상황이라면 업데이트 안 함
        return;
    //1. snake & item 업데이트
    snake->setDirection(s_state); 

    //몬스터 추가여부
    Uint32 currentTime = SDL_GetTicks(); // 현재 시간을 가져옵니다.
    // 30초(30000밀리초)이 지났는지 확인합니다.
    if (currentTime - lastMonsterAddedTime >= 30000 && monsterList.size()<20) {
        // 30초가 지났다고 20개가 안된다면 새로운 몬스터를 추가합니다.
        Monster* newMonster = new Monster(snake->getSnakeList());
        monsterList.push_back(newMonster);
        lastMonsterAddedTime = currentTime; // 몬스터를 추가한 시간을 업데이트합니다.
    }
    
    //1.1 snake가 item과 충돌했다면
    if (snake->isCollidingItem(item,s_state)) {
        snake->eatItem(item->getItemPower());//길이 증가
        item->spawn(snake->getSnakeList()); //item 위치 리스폰
    }
    //1.2 snake가 자신의 몸과 충돌했다면
    if (snake->isCollidingSelf(s_state))
        snakeGame_running = 2;
    //1.3 snake가 벽과 충돌했다면
    if (snake->isCollidingWall(s_state))
        snakeGame_running = 2;


    for (const auto& monster : monsterList)
        monster->move();
    
    // 뱀의 움직임 업데이트 후에 충돌을 확인합니다.
    int flag = false; //중복 충돌판단 방지
    for (const auto& monster : monsterList) {
        if (snake->isCollidingMonster(monster, s_state)) {
            snakeGame_running = 2;
            flag = true;
            break;
        }
    }

    if (snakeGame_running == 1) {
        snake->move();

        //시간 업데이트
        
        Uint32 current_ticks = SDL_GetTicks();
        time_ms_ += current_ticks - last_ticks_;
        UpdateTimeTexture(time_ms_);	// 업데이트 된 시간(time_ms_)을 문자로 변환한 후 texture로 만든다.

        last_ticks_ = current_ticks;
    }

    //몬스터 충돌 체크
    if (!flag) {
        for (const auto& monster : monsterList) {
            if (snake->isCollidingMonster(monster, s_state)) {
                snakeGame_running = 2;
                break;
            }
        }
    }
    
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
            if (snakeGame_running == 2) //죽었으면 키 이벤트 안 받음
                break;

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (snakeGame_running == 1) {//게인 진행 중이었으면 일시중지로
                    snakeGame_running = 3;
                    // 일시정지를 시작할 때 시간을 업데이트합니다.
                    Uint32 current_ticks = SDL_GetTicks();
                    time_ms_ += current_ticks - last_ticks_;
                    pauseStartTime = SDL_GetTicks();
                }
                else if (snakeGame_running == 3) {//일시정지였으면 게임 중으로
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks(); 
                    lastMonsterAddedTime += SDL_GetTicks() - pauseStartTime; // 일시정지 시간만큼 더해줍니다.
                }
            }
            if (snakeGame_running == 3) //일시정지 중이면 키 이벤트 안 받음
                break;

            /////방향키 다운
            //방향키 누르는 순간 정지가 풀리며 계속 이동
            if (event.key.keysym.sym == SDLK_LEFT) {
                s_state = 0; //현재 눌린 값이 LEFT
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                s_state = 1;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                s_state = 2;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                s_state = 3;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
                }
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
    //몬스터 객체 삭제 했다가 재생성
    for (const auto& mon : monsterList) {
        delete mon;
    }
    monsterList.clear(); // 몬스터 리스트를 비웁니다.

    

    for (int i = 0;i < 2;i++) {
        monsterList.push_back(new Monster(snake->getSnakeList()));
    }
    

    //item 재배치
    item->spawn(snake->getSnakeList());
    UpdateScoreTexture();

    //time 초기화
    time_ms_ = 0;
    
    UpdateTimeTexture(time_ms_);
    //lastMonsterAddedTime = SDL_GetTicks(); // 게임 시작
}


SnakeGame::~SnakeGame() {
    //이미지 텍스쳐 해제
    SDL_DestroyTexture(item_texture);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(monster_texture);
    SDL_DestroyTexture(stop_texture);

    //폰트 텍스쳐 해제
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(readme);
    SDL_DestroyTexture(snake_length);
    SDL_DestroyTexture(snake_score);
    SDL_DestroyTexture(text_time);
    

    // 몬스터 객체 삭제
    for (const auto& monster : monsterList) {
        delete monster;
    }
    monsterList.clear(); // 몬스터 리스트를 비웁니다.


    delete item;
    delete snake;
}
