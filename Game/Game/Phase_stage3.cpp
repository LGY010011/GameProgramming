#include "Phase_stage3Game.h"
#include <Windows.h>
#include <iomanip>
#include <string>

extern default_random_engine generator;

void Stage3::UpdateScoreTexture()
{
    if (myBell_ != 0)
    {
        SDL_DestroyTexture(myBell_);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        myBell_ = 0;
    }

    std::string str = std::to_string(bell->getCount());
    SDL_Surface* tmp_surface = TTF_RenderText_Blended(font, str.c_str(), { 255,255,255 });

    myBell_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
}

Stage3::Stage3() {
    //1. 객체 생성
    //a. 종 생성
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);


    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    //b. 까치 생성
    magpie = new Magpie(3, 3, 1, 50, 0); //(0,0)에서 시작, speed는 1,hp는 100으로 설정
    //c. 구렁이 생성
    snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY());
    //d. 폭탄 생성
    bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));

    ////2. 텍스쳐 가져오기
    //a. 종 텍스쳐
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/stage3/bell.png");
    bell_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bell_destination_rect.x = bell->getX();
    bell_destination_rect.y = bell->getY();
    bell_destination_rect.w = GRID_STAGE3;
    bell_destination_rect.h = GRID_STAGE3;

    //b. 까치 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resources/stage3/magpie.png");
    magpie_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    magpie_destination_rect.x = magpie->getX() * GRID_STAGE3;
    magpie_destination_rect.y = magpie->getY() * GRID_STAGE3;
    magpie_destination_rect.w = GRID_STAGE3;
    magpie_destination_rect.h = GRID_STAGE3;


    //c. 구렁이 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeHead.png");
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    snake_destination_rect.x = snake->getSnakeList().front()->sX;
    snake_destination_rect.y = snake->getSnakeList().front()->sY;
    snake_destination_rect.w = GRID_STAGE3;
    snake_destination_rect.h = GRID_STAGE3;

    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeBody.png");
    snakeBody_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeTail.png");
    snakeTail_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수


    //폭탄 텍스쳐 
    temp_sheet_surface = IMG_Load("../../Resources/stage3/bombAfter.png");
    bombAfter_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bomb_source_rect.x = 0;
    bomb_source_rect.y = 0;
    bomb_source_rect.w = 32;
    bomb_source_rect.h = 32;

    bomb_destination_rect.w = GRID_STAGE3 * 3;
    bomb_destination_rect.h = GRID_STAGE3 * 3;

    //d. 배경 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resources/stage3/background.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bg_destination_rect.x = GRID_STAGE3;
    bg_destination_rect.y = GRID_STAGE3;
    bg_destination_rect.w = screenWidth - GRID_STAGE3 * 2;
    bg_destination_rect.h = screenHeight - GRID_STAGE3 * 2;

    temp_sheet_surface = IMG_Load("../../Resources/stage3/red.png");
    red_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/wait.png");
    wait_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    //하트 텍스처
    temp_sheet_surface = IMG_Load("../../Resources/stage3/heartZero.png");
    heartZero_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/heartHalf.png");
    heartHalf_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/heartOne.png");
    heartOne_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    heart_destination_rect.w = GRID_STAGE3 - 15;
    heart_destination_rect.h = GRID_STAGE3 - 15;

    //버튼 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resources/stage3/continue.png");
    button_continue = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    continue_destination_rect = { 490,270,100,100 };

    temp_sheet_surface = IMG_Load("../../Resources/stage3/main.png");
    button_main = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    main_destination_rect = { 490,370,100,100 };



    //글씨 텍스쳐 만들기,,
    myBell_destination.x = screenWidth - GRID_STAGE3 * 2;
    myBell_destination.y = GRID_STAGE3 + 5;
    myBell_destination.w = GRID_STAGE3 - 10;
    myBell_destination.h = GRID_STAGE3 - 5;

    ready_texture = SDL_CreateTextureFromSurface(g_renderer, TTF_RenderText_Blended(font, "READY", { 255,255,255 }));

    readyCount_destination.x = screenWidth / 2 - 100;
    readyCount_destination.y = screenHeight / 2 - 50;
    readyCount_destination.w = 200;
    readyCount_destination.h = 100;


    //음악 가져오기
    background_music = Mix_LoadMUS("../../Resources/stage3/stage3.mp3");
    Mix_VolumeMusic(90);

    bell_sound = Mix_LoadWAV("../../Resources/stage3/bell.wav");
    Mix_VolumeChunk(bell_sound, 128);


    bombPrev_sound = Mix_LoadWAV("../../Resources/stage3/bomb_prev.wav");
    Mix_VolumeChunk(bombPrev_sound, 128);
    bombAfter_sound = Mix_LoadWAV("../../Resources/stage3/bomb_After.wav");
    Mix_VolumeChunk(bombAfter_sound, 90);
    button_sound = Mix_LoadWAV("../../Resources/stage3/pauseSound.wav");
    Mix_VolumeChunk(button_sound, 128);

    //2. 기타 세팅
    f_state = STOP;//방향키 안 누름
    stop = true; //정지 상황으로 초기화
    key_pushed.clear();//키 정보 초기화



    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;
    stage3_startTime = 0;
    lastBombTime = 0;

    stage3_status = 0;

    alpha = 0;

    pauseStartTime = 0;
    totalPauseTime = 0;
    totalPauseTime_2 = 0;
    UpdateScoreTexture();

}


void Stage3::HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (stage3_status == 1) {//게인 진행 중이었으면 일시중지로
                    stage3_status = 2;
                    pauseStartTime = SDL_GetTicks();
                    totalPauseTime = 0;

                    Mix_PauseMusic(); // 배경음악 일시정지
                    for (int i = 0; i < MIX_CHANNELS; i++) {
                        Mix_Pause(i); // 모든 채널의 사운드 일시정지
                    }
                }

            }
            if (stage3_status == 2) {//일시정지 상태면 키 입력 받지 않음
                break;
            }
            /////////////방향키 조작

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = LEFT; //현재 눌린 값이 LEFT
                stop = false;
                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    /// Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = RIGHT;

                stop = false;


                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    ///Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = UP;

                stop = false;


                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();

                }
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = DOWN;

                stop = false;

                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    //Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }
            }
            if (std::find(key_pushed.begin(), key_pushed.end(), f_state) == key_pushed.end())
                key_pushed.push_front(f_state);//눌린 키 정보 저장

            break;

        case SDL_KEYUP:

            if (event.key.keysym.sym == SDLK_LEFT) {
                key_pushed.remove(LEFT);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                key_pushed.remove(RIGHT);

            }
            else if (event.key.keysym.sym == SDLK_UP) {
                key_pushed.remove(UP);

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                key_pushed.remove(DOWN);



            }

            if (key_pushed.empty())
                stop = true;


            break;

        case SDL_MOUSEBUTTONDOWN:

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (stage3_status == 2) {//일시정지 상태라면

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= continue_destination_rect.x && mouse_x <= continue_destination_rect.x + continue_destination_rect.w &&
                        mouse_y >= continue_destination_rect.y && mouse_y <= continue_destination_rect.y + continue_destination_rect.h
                        )//계속하기 버튼 누름
                    {
                        Mix_PlayChannel(-1, button_sound, 0);//효과음 출력

                        stage3_status = 1;
                        totalPauseTime = SDL_GetTicks() - pauseStartTime;
                        totalPauseTime_2 += totalPauseTime;
                        Mix_ResumeMusic(); // 배경음악 재생 재개
                        for (int i = 0; i < MIX_CHANNELS; i++) {
                            Mix_Resume(i); // 모든 채널의 사운드 재생 재개
                        }
                    }
                    else if (mouse_x >= main_destination_rect.x && mouse_x <= main_destination_rect.x + main_destination_rect.w &&
                        mouse_y >= main_destination_rect.y && mouse_y <= main_destination_rect.y + main_destination_rect.h
                        )//메인으로 버튼 누름
                    {
                        Mix_PlayChannel(-1, button_sound, 0);//효과음 출력
                        g_current_game_phase = PHASE_INTRO;
                        game_result = 0;
                        if (Mix_PlayingMusic()) {
                            Mix_HaltMusic();
                        }
                    }
                }

            }
            break;
        }
    }
}
void Stage3::Update() {
    /*cout << "방향키 : ";
    for (int i : key_pushed) {
        cout << i << " ";
    }
    cout << endl;*/
    if (stage3_status == 0 || stage3_status == 2) //키 대기 혹은 일시정지  == stage3_status == 2
        return;



    //1. 까치
    //1.1 까치 좌표 업데이트
    int x = magpie->getX();
    int y = magpie->getY();
    if (!stop) { //정지가 아니라면 까치 이동
        if (key_pushed.front() == LEFT) { //좌측이동
            x -= 1;
            flip = SDL_FLIP_NONE;
        }
        else if (key_pushed.front() == RIGHT) {//우측이동
            x += 1;
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (key_pushed.front() == UP) {//위로 이동
            y -= 1;
        }
        else if (key_pushed.front() == DOWN) {//아래로 이동
            y += 1;
        }

    }

    //1.2 까치 좌표 범위
    if (x > screenWidth / GRID_STAGE3 - 2) {
        x = 1;
    }
    else if (x < 1) {
        x = screenWidth / GRID_STAGE3 - 2;
    }
    if (y > screenHeight / GRID_STAGE3 - 2) {
        y = 1;
    }
    else if (y < 1) {
        y = screenHeight / GRID_STAGE3 - 2;
    }
    //1.3 까치 이동
    magpie->move(x, y);

    //1.4 까치 무적 시간 업데이트
    if (magpie->getInvincible() && (SDL_GetTicks() - magpie->getLastDamageTime() >= 2000)) {
        magpie->setInvincible(false);
    }


    //2. 구렁이 업데이트
    //구렁이 속도 조절
    int time = SDL_GetTicks();
    if (snake->getN() > 5 && time - lastSpeedUpTime > 10000) {
        //cout<<snake->getN()<<endl;
        snake->setN(snake->getN() - 1);
        // 속도 증가 시간 업데이트
        // 속도 증가 시간 업데이트
        lastSpeedUpTime = time;
    }
    //구렁이 이동
    snake->move(magpie->getX(), magpie->getY());


    //3. 폭탄 업데이트
    // 게임시작 후 20초마다 bomb 추가 -> 랜덤하게 터지는 애랑 까치 쫓아오는 애
    int currentTime = SDL_GetTicks() - totalPauseTime;
    if ((currentTime - lastBombTime) >= 7000 && bombList.size() < 10) {
        // bomb을 추가하는 코드를 여기에 작성합니다.
        uniform_int_distribution<int> distribution(0, 2);
        bombList.push_back(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, distribution(generator)));
        lastBombTime = currentTime;

    }

    for (const auto& bomb : bombList) {
        //cout<<i << ": checkCount: " << bomb->getCheckCount() << endl;
        if (bomb->getCheckCount() >= bomb->getLastCount())
            bomb->setCheckCount(bomb->getStartCount()); //재설정
        bomb->setCheckCount(bomb->getCheckCount() + 1); //카운트 개수 증가
        if (bomb->getType() == 1) {
            bomb->move(magpie->getX(), magpie->getY()); //타겟 좌표 변경 -> 0 이하일 때만 값 변경됨
        }
        else {
            uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
            uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);
            bomb->move(distributionX(generator), distributionY(generator)); //타겟 좌표 변경 -> 0 이하일 때만 값 변경됨
        }


    }

    //3. 충돌 확인
    //3.1 종 충돌 확인
    if (magpie->isCollidingBell(bell)) {//bell이랑 부딪혔다면
        bell->setCount(bell->getCount() + 1); //count개수 하나 증가
        Mix_PlayChannel(3, bell_sound, 0);

    }
    //5초가 지났다면 종 위치 갱신
    int current = SDL_GetTicks() - totalPauseTime;
    if (current - bell->getLastEatenTime() > 5000) { // 5초가 지났다면
        bell->spawn();//종 위치 갱신
        bell->setLastEatenTime(current); // 재생성 시간 초기화
    }

    //3.2 구렁이 충돌 확인
    if (magpie->isCollidingSnake(snake)) { //snake랑 부딪혔다면 hp 깎임
        //Mix_PlayChannel(-1, hit_sound, 0);
        magpie->GetAttackted(snake->getAttackPower());//데미지 받음

    }


    //3.3 폭탄 충돌 확인 + 음향 출력
    for (const auto& bomb : bombList) {
        //충돌 확인
        if (bomb->getCheckCount() >= bomb->getMiddleCount() && bomb->getCheckCount() < bomb->getLastCount()) {
            if (magpie->isCollidingBomb(bomb)) {
                magpie->GetAttackted(bomb->getAttackPower());
                //Mix_PlayChannel(-1, hit_sound, 0);
            }
        }
        //음향 출력
        int b_count = bomb->getCheckCount();
        //카운트가 50이면 타임시작
        if (b_count == 0) {
            Mix_PlayChannel(-1, bombPrev_sound, 0);
        }
        else if (b_count == bomb->getMiddleCount()) {
            Mix_PlayChannel(-1, bombAfter_sound, 0);
        }

    }

    //4. 종료 조건 확인
    //엔딩페이즈 넘어가기 전 딜레이 주는거 지금 여기에 해놨는데
    //합치고 나서 메인에서 prev랑 current 비교해서 해야 더 자연스러울 듯
    if (bell->getCount() == 5) {//종 5개 모았으면 
        game_result = 1; //승리
        g_current_game_phase = PHASE_STAGE3_ENDING;
        viewedEndings[2][1] = true;
        SDL_Delay(1000);
    }

    if (magpie->getHealth() <= 0) {
        game_result = 2; //실패
        g_current_game_phase = PHASE_STAGE3_ENDING;
        viewedEndings[2][0] = true;
        SDL_Delay(1000);
    }


}
void Stage3::Render() {

    //// 1. 배경 그리기.
    // 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
    // <windows.h>에서 제공하는 함수를 사용한다

    //// 1.2. 배경 그리기

    // 붉은 배경 오퍼시티 조절
    if (stage3_status == 1) {
        int time = SDL_GetTicks() - stage3_startTime - totalPauseTime_2;
        if (time < 60000) { // 1분 동안 점차 붉어짐
            alpha = time / 60000.0 * 255;
            if (alpha > 70)
                alpha = 70;
        }
    }

    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);


    //// 2. 캐릭터 그리기.
    // 종 그리기
    bell_destination_rect.x = bell->getX() * GRID_STAGE3; //그려질 좌표 지정
    bell_destination_rect.y = bell->getY() * GRID_STAGE3;
    SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);

    // 폭탄 그리기
    for (const auto& bomb : bombList) {
        int b_count = bomb->getCheckCount();
        //카운트가 50보다 작고 0 이상인데 짝수면 ? 출력
        if (b_count < bomb->getMiddleCount() && b_count >= 0) {
            if (b_count % 2 == 0) {
                bell_destination_rect.x = bomb->getBombRange()[4].x * GRID_STAGE3;
                bell_destination_rect.y = bomb->getBombRange()[4].y * GRID_STAGE3;
                SDL_SetTextureColorMod(bell_texture, 200, 50, 50);
                SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);
                SDL_SetTextureColorMod(bell_texture, 255, 255, 255);

            }
        }

        //카운트가 100에서 150 사이면 !출력
        else if (b_count >= bomb->getMiddleCount() && b_count < bomb->getLastCount()) {
            bombAttack* b = bomb->getBombRange();

            if (b_count % 3 == 0) {
                int i = (b_count / 3) % 17;
                bomb_source_rect.x = 32 * i; // 0 32 64 
            }

            bomb_destination_rect.x = b[0].x * GRID_STAGE3;
            bomb_destination_rect.y = b[0].y * GRID_STAGE3;

            SDL_RenderCopy(g_renderer, bombAfter_texture, &bomb_source_rect, &bomb_destination_rect);

        }
    }

    // 구렁이 그리기
    auto snakeList = snake->getSnakeList();
    auto last = --snakeList.end();
    int angle = 0;
    int prevD = LEFT;
    int shiftX = 0, shiftY = 0;

    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->sX * (GRID_STAGE3); // 그려질 좌표 지정
        snake_destination_rect.y = (*it)->sY * (GRID_STAGE3);

        //각도 설정
        switch ((*it)->dircetion) {
        case LEFT://좌
            angle = -90;
            break;
        case RIGHT://우
            angle = 90;
            break;
        case UP://위
            angle = 0;
            break;
        case DOWN://아래
            angle = 180;
            break;
        default:
            break;
        }


        // 뱀의 헤드 노드인 경우에는 헤드 이미지를 사용하고, 그렇지 않은 경우에는 기존의 뱀 이미지를 사용합니다.
        if (it == snakeList.begin()) {
            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);
        }
        else if (it == last) {
            switch (prevD) {
            case LEFT://좌
                angle = -90;
                break;
            case RIGHT://우
                angle = 90;
                break;
            case UP://위
                angle = -0;
                break;
            case DOWN://아래
                angle = 180;

                break;
            default:
                break;
            }
            SDL_RenderCopyEx(g_renderer, snakeTail_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            SDL_RenderCopyEx(g_renderer, snakeBody_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }

        prevD = (*it)->dircetion;
    }


    // 까치 그리기
    magpie_destination_rect.x = magpie->getX() * GRID_STAGE3; //그려질 좌표 지정
    magpie_destination_rect.y = magpie->getY() * GRID_STAGE3;

    // 까치 렌더링
    if (magpie->getInvincible()) {
        SDL_SetTextureColorMod(magpie_texture, 255, 120, 120); // 빨간색으로 변경
    }
    else {
        SDL_SetTextureColorMod(magpie_texture, 255, 255, 255); // 원래 색상으로 변경
    }
    if (!magpie->getInvincible() || SDL_GetTicks() % 500 < 250) { // 무적 상태가 아니거나 0.25초 간격으로 깜빡거림
        SDL_RenderCopyEx(g_renderer, magpie_texture, NULL, &magpie_destination_rect, 0, NULL, flip);
    }



    //하트 출력
    int hp = (int)magpie->getHealth();

    // 하트 렌더링
    for (int i = 0; i < 5; i++) {

        heart_destination_rect.x = i * (GRID_STAGE3)+GRID_STAGE3 + 5;
        heart_destination_rect.y = 0 + GRID_STAGE3 + 5;

        if (magpie->getInvincible()) {
            int timeSinceDamage = SDL_GetTicks() - magpie->getLastDamageTime();
            if (timeSinceDamage < 100) {
                // 0.125초와 0.375초에 하트를 흔듬
                if ((timeSinceDamage % 100) < 20 || (timeSinceDamage % 100) > 80) {
                    heart_destination_rect.y += 10; // y 좌표를 흔듬
                }
            }

        }

        if (hp / 10 != 0) {
            SDL_RenderCopy(g_renderer, heartOne_texture, NULL, &heart_destination_rect);
        }
        else if (hp % 10 == 5) {
            SDL_RenderCopy(g_renderer, heartHalf_texture, NULL, &heart_destination_rect);
        }
        else if (hp <= 0) {
            SDL_RenderCopy(g_renderer, heartZero_texture, NULL, &heart_destination_rect);

        }
        if (hp <= 0)
            continue;
        hp -= 10;
    }

    //모은 종 개수 출력 -> 아직 안 함
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, myBell_, NULL, &myBell_destination);


    //// 3. 프레임 완성.
    // std::cout으로 출력한 내용 중, 아직 화면에 표시되 않고 버퍼에 남아 있는 것이 있다면, 모두 화면에 출력되도록 한다.
    //붉은 이미지 적용
    SDL_SetTextureAlphaMod(red_texture, alpha);
    SDL_RenderCopy(g_renderer, red_texture, NULL, &bg_destination_rect);
    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);

    if (stage3_status != 1) {//일시정지 상태 혹은 대기 상태
        SDL_RenderCopy(g_renderer, wait_texture, NULL, &bg_destination_rect);
        switch (stage3_status)
        {
        case 0:
            //대기 렌더
            SDL_RenderCopy(g_renderer, ready_texture, NULL, &readyCount_destination);
            break;
        case 2:
            //버튼 렌더

            SDL_RenderCopy(g_renderer, button_continue, NULL, &continue_destination_rect);
            SDL_RenderCopy(g_renderer, button_main, NULL, &main_destination_rect);
            break;
        default:
            break;
        }
    }
    SDL_RenderPresent(g_renderer);

}


void Stage3::Reset() {
    //객체 초기화
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();

    //a. 종 생성
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);
    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    //b. 까치 생성
    magpie = new Magpie(3, 3, 1, 50, 0); //(0,0)에서 시작, speed는 1,hp는 100으로 설정
    //c. 구렁이 생성
    snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY());

    //d. 폭탄 생성
    bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));


    //2. 기타 세팅
    f_state = STOP;//방향키 안 누름
    stop = true; //정지 상황으로 초기화
    key_pushed.clear();//키 정보 초기화

    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;
    alpha = 0;
    stage3_status = 0;

    //음향 끄기
    Mix_HaltChannel(-1);//모든 사운드 중지

    //음악 다시 시작
    Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작


    //일시정지 시간 초기화
    totalPauseTime = 0;
    stage3_startTime = 0;
    lastBombTime = 0;
    pauseStartTime = 0;
    totalPauseTime_2 = 0;
}


Stage3::~Stage3() {
    //이미지 텍스쳐 해제
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(snakeBody_texture);
    SDL_DestroyTexture(snakeTail_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bell_texture);
    SDL_DestroyTexture(magpie_texture);
    SDL_DestroyTexture(heartZero_texture);
    SDL_DestroyTexture(heartHalf_texture);
    SDL_DestroyTexture(heartOne_texture);
    SDL_DestroyTexture(bombAfter_texture);
    SDL_DestroyTexture(red_texture);
    SDL_DestroyTexture(ready_texture);
    SDL_DestroyTexture(wait_texture);
    SDL_DestroyTexture(button_continue);
    SDL_DestroyTexture(button_main);
    SDL_DestroyTexture(myBell_);


    //음악 해제
    Mix_FreeMusic(background_music);
    Mix_FreeChunk(bell_sound);

    Mix_FreeChunk(bombPrev_sound);
    Mix_FreeChunk(bombAfter_sound);
    Mix_FreeChunk(button_sound);



    //객체 해제
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();

}