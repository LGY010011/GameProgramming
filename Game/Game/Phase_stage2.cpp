#include "Phase_stage2Game.h"
#include <Windows.h>
#include <SDL_image.h> 
#include <iomanip>

using namespace std;

//미로
//배경 텍스쳐

SDL_Rect stage2_bg_source_rect;

Stage2::Stage2() {

    uniform_int_distribution<int> distributionX(0, SCREEN_WIDTH_STAGE2);
    uniform_int_distribution<int> distributionY(0, SCREEN_HEIGHT_STAGE2);
    rabbit = new Rabbit(distributionX(generator), distributionY(generator), 1, 3);
    turtle = new Turtle(1, 1, 0, 3, 0);
    coral = new Coral(0, 0, 0, 0, 1);
    coral2 = new Coral2(0, 0, 0, 0, 1);
    // 기존 Conch 객체 생성
    conch1 = new Conch(15, 15, 0, 0, 1, 0, 0);
    conch2 = new Conch(10, 10, 0, 0, 1, 0, 0);
    conch3 = new Conch(20, 3, 0, 0, 1, 0, 0);
    conch4 = new Conch(25, 25, 0, 0, 1, 0, 0);

    rabbitSpawnTimer = RABBIT_SPAWN_TIME;
    coral2_spawn_timer = CORAL2_SPAWN_TIME; // CORAL2_SPAWN_TIME은 coral2가 나타나고 사라지는 시간 간격
    coral2_visible = false; // 처음에는 coral2를 표시하지 않음

    coral3_spawn_timer = CORAL2_SPAWN_TIME; // CORAL2_SPAWN_TIME은 coral2가 나타나고 사라지는 시간 간격=>추가
    coral3_visible = true; //=>추가

    // 배경 텍스쳐 로드
    SDL_Surface* stage2_bg_surface = IMG_Load("../../Resources/stage2/stage2/stage2_bg.png");
    stage2_bg_texture = SDL_CreateTextureFromSurface(g_renderer, stage2_bg_surface);
    SDL_FreeSurface(stage2_bg_surface);
    stage2_bg_source_rect = { 0, 0, 750, 600 };
    stage2_bg_destination_rect = { TILE_SIZE,TILE_SIZE , 1080, 600 };

    //배경배경 텍스처 로드
    SDL_Surface* stage2_bgbg_surface = IMG_Load("../../Resources/stage2/stage2/stage2_bgbg.png");
    stage2_bgbgbg_texture = SDL_CreateTextureFromSurface(g_renderer, stage2_bgbg_surface);
    stage2_bgbgbg_destination_rect = { 0, 0, 1080, 720 };
    SDL_FreeSurface(stage2_bgbg_surface);


    //거북이 텍스쳐 로드
    SDL_Surface* turtle_surface = IMG_Load("../../Resources/stage2/stage2/stage2_turtle.png");
    turtle_texture = SDL_CreateTextureFromSurface(g_renderer, turtle_surface);
    SDL_FreeSurface(turtle_surface);
    turtle_destination_rect.x = turtle->getX() * GRID_stage2;
    turtle_destination_rect.y = turtle->getY() * GRID_stage2;
    turtle_destination_rect.w = GRID_stage2;
    turtle_destination_rect.h = GRID_stage2;

    //거북이2 텍스쳐 로드=>추가
    SDL_Surface* turtle2_surface = IMG_Load("../../Resources/stage2/stage2/stage2_turtle2.png");
    turtle2_texture = SDL_CreateTextureFromSurface(g_renderer, turtle2_surface);
    SDL_FreeSurface(turtle2_surface);
    turtle_destination_rect.x = turtle->getX() * GRID_stage2;
    turtle_destination_rect.y = turtle->getY() * GRID_stage2;
    turtle_destination_rect.w = GRID_stage2;
    turtle_destination_rect.h = GRID_stage2;

    //토끼 텍스쳐 로드
    SDL_Surface* rabbit_surface = IMG_Load("../../Resources/stage2/stage2/stage2_rabbit.png");
    rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, rabbit_surface);
    SDL_FreeSurface(rabbit_surface);
    rabbit_destination_rect.x = rabbit->getX() * GRID_stage2;
    rabbit_destination_rect.y = rabbit->getY() * GRID_stage2;
    rabbit_destination_rect.w = GRID_stage2;
    rabbit_destination_rect.h = GRID_stage2;

    //산호 텍스쳐 로드
    SDL_Surface* coral_surface = IMG_Load("../../Resources/stage2/stage2/stage2_coral2.png");
    coral_texture = SDL_CreateTextureFromSurface(g_renderer, coral_surface);
    SDL_FreeSurface(coral_surface);
    coral_destination_rect.x = coral->getX() * GRID_stage2;
    coral_destination_rect.y = coral->getY() * GRID_stage2;
    coral_destination_rect.w = GRID_stage2;
    coral_destination_rect.h = GRID_stage2;

    //산호2 텍스쳐 로드
    SDL_Surface* coral2_surface = IMG_Load("../../Resources/stage2/stage2/stage2_coral.png");
    coral2_texture = SDL_CreateTextureFromSurface(g_renderer, coral2_surface);
    SDL_FreeSurface(coral2_surface);
    coral2_destination_rect.x = coral->getX() * GRID_stage2;
    coral2_destination_rect.y = coral->getY() * GRID_stage2;
    coral2_destination_rect.w = GRID_stage2;
    coral2_destination_rect.h = GRID_stage2;


    //간 텍스쳐 로드
    SDL_Surface* gan_surface = IMG_Load("../../Resources/stage2/stage2/stage2_gan.png");
    gan_texture = SDL_CreateTextureFromSurface(g_renderer, gan_surface);
    SDL_FreeSurface(gan_surface);
    gan_destination_rect.x = 0;
    gan_destination_rect.y = 0;
    gan_destination_rect.w = GRID_stage2;
    gan_destination_rect.h = GRID_stage2;

    //하트0 텍스쳐 로드
    SDL_Surface* heart0_surface = IMG_Load("../../Resources/stage2/stage2/stage2_heart0.png");
    heart0_texture = SDL_CreateTextureFromSurface(g_renderer, heart0_surface);
    SDL_FreeSurface(heart0_surface);
    heart0_destination_rect.x = 0;
    heart0_destination_rect.y = 0;
    heart0_destination_rect.w = GRID_stage2;
    heart0_destination_rect.h = GRID_stage2;

    //하트2 텍스쳐 로드
    SDL_Surface* heart2_surface = IMG_Load("../../Resources/stage2/stage2/stage2_heart2.png");
    heart2_texture = SDL_CreateTextureFromSurface(g_renderer, heart2_surface);
    SDL_FreeSurface(heart2_surface);
    heart2_destination_rect.x = 0;
    heart2_destination_rect.y = 0;
    heart2_destination_rect.w = GRID_stage2;
    heart2_destination_rect.h = GRID_stage2;

    //소라게 텍스쳐 로드
    SDL_Surface* conch_surface = IMG_Load("../../Resources/stage2/stage2/stage2_conch.png");
    conch_texture = SDL_CreateTextureFromSurface(g_renderer, conch_surface);
    SDL_FreeSurface(conch_surface);
    conch_destination_rect.x = conch1->getX() * GRID_stage2;
    conch_destination_rect.y = conch1->getY() * GRID_stage2;
    conch_destination_rect.w = GRID_stage2;
    conch_destination_rect.h = GRID_stage2;

    //wait_texture 이미지
    SDL_Surface* wait_surface = IMG_Load("../../Resources/stage2/wait.png");
    wait_texture = SDL_CreateTextureFromSurface(g_renderer, wait_surface);
    SDL_FreeSurface(wait_surface);//해제 필수
    wait_destination_rect = { 0,0,1080,720 };


    //버튼 텍스쳐
    SDL_Surface* continue_btn = IMG_Load("../../Resources/stage2/continue.png");
    button_continue = SDL_CreateTextureFromSurface(g_renderer, continue_btn);
    SDL_FreeSurface(continue_btn);//해제 필수
    continue_destination_rect = { 490,270,100,100 };

    SDL_Surface* main_btn = IMG_Load("../../Resources/stage2/main.png");
    button_main = SDL_CreateTextureFromSurface(g_renderer, main_btn);
    SDL_FreeSurface(main_btn);//해제 필수
    main_destination_rect = { 490,370,100,100 };

    //글씨 텍스쳐 만들기,,
    ready_texture = SDL_CreateTextureFromSurface(g_renderer, TTF_RenderText_Blended(font, "READY", { 255,255,255 }));

    readyCount_destination.x = screenWidth / 2 - 100;
    readyCount_destination.y = screenHeight / 2 - 50;
    readyCount_destination.w = 200;
    readyCount_destination.h = 100;



    //음향
    //음악 가져오기
    background_music = Mix_LoadMUS("../../Resources/stage2/stage2.mp3");
    Mix_VolumeMusic(90);

    rabbit_sound = Mix_LoadWAV("../../Resources/stage2/stage2_rabbitSound.mp3");//토끼 부딪힐때 소리
    Mix_VolumeChunk(rabbit_sound, 128);

    //거북이 산호 부딪힐때 소리
    coral_sound = Mix_LoadWAV("../../Resources/stage2/stage2_coralSound.mp3");
    Mix_VolumeChunk(coral_sound, 128);

    //소라게 부딪힐때 소리
    conch_sound = Mix_LoadWAV("../../Resources/stage2/stage2_conchSound.mp3");
    Mix_VolumeChunk(conch_sound, 128);

    //버튼 누를때 소리
    button_sound = Mix_LoadWAV("../../Resources/stage2/pauseSound.wav");
    Mix_VolumeChunk(button_sound, 128);


    //기타
    f_state = -1;
    stop = true;
    for (int i = 0; i < 4; i++) {
        f_list[i] = false;
    }
    game_result = 0;

    flip = SDL_FLIP_HORIZONTAL;


    stage2_startTime = 0;
    stage2_status = 0;

    alpha = 0;

    pauseStartTime = 0;
    totalPauseTime = 0;
    totalPauseTime_2 = 0;
    system("cls");
}

void Stage2::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_flag_running = false;
            break;
        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (stage2_status == 1) {//게인 진행 중이었으면 일시중지로
                    stage2_status = 2;
                    pauseStartTime = SDL_GetTicks();
                    totalPauseTime = 0;

                    Mix_PauseMusic(); // 배경음악 일시정지
                    for (int i = 0; i < MIX_CHANNELS; i++) {
                        Mix_Pause(i); // 모든 채널의 사운드 일시정지
                    }
                }
                else if (stage2_status == 2) {//일시정지였으면 게임 중으로
                    stage2_status = 1;
                    Mix_ResumeMusic(); // 배경음악 재생 재개
                    for (int i = 0; i < MIX_CHANNELS; i++) {
                        Mix_Resume(i); // 모든 채널의 사운드 재생 재개
                    }
                }
            }
            if (stage2_status == 2) {
                break;
            }


            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = LEFT; //현재 눌린 값이 LEFT
                f_list[f_state] = true;
                stop = false;
                if (stage2_status == 0) {
                    stage2_status = 1;
                    stage2_startTime = SDL_GetTicks();
                    // Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = RIGHT;
                f_list[f_state] = true;
                stop = false;

                if (stage2_status == 0) {
                    stage2_status = 1;
                    stage2_startTime = SDL_GetTicks();
                    // Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = UP;
                f_list[f_state] = true;
                stop = false;
                if (stage2_status == 0) {
                    stage2_status = 1;
                    stage2_startTime = SDL_GetTicks();
                    //  Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
                }
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = DOWN;
                f_list[f_state] = true;
                stop = false;
                if (stage2_status == 0) {
                    stage2_status = 1;
                    stage2_startTime = SDL_GetTicks();
                    // Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작
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

            if (f_list[0])
                f_state = 0;
            if (f_list[1])
                f_state = 1;
            if (f_list[2])
                f_state = 2;
            if (f_list[3])
                f_state = 3;
            if (f_list[0] != true && f_list[1] != true && f_list[2] != true && f_list[3] != true)
                stop = true;

            break;
        case SDL_MOUSEBUTTONDOWN:

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (stage2_status == 2) {//일시정지 상태라면

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= continue_destination_rect.x && mouse_x <= continue_destination_rect.x + continue_destination_rect.w &&
                        mouse_y >= continue_destination_rect.y && mouse_y <= continue_destination_rect.y + continue_destination_rect.h
                        )//계속하기 버튼 누름
                    {
                        Mix_PlayChannel(-1, button_sound, 0);//효과음 출력

                        stage2_status = 1;
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

void Stage2::Update() {

    if (stage2_status == 0 || stage2_status == 2) //키 대기 혹은 일시정지
        return;

    conch1->move(0, 0);
    conch2->move(0, 0);
    conch3->move(0, 0);
    conch4->move(0, 0);

    if (turtle->isInvincible()) {
        int timer = turtle->getInvincibleTimer();
        timer--;
        if (timer <= 0) {
            turtle->setInvincible(false); // 무적 상태 해제
            timer = 0; // 타이머 초기화
        }
        turtle->setInvincibleTimer(timer);
    }
    // 게임 루프에서 타이머를 감소시킴
    rabbitSpawnTimer--;

    // 타이머가 0이 되면 토끼를 리스폰하고 타이머를 재설정함
    if (rabbitSpawnTimer <= 0) {
        rabbit->spawn(); // 토끼 리스폰
        rabbitSpawnTimer = RABBIT_SPAWN_TIME; // 타이머 초기화
    }

    // coral2_spawn_timer를 감소시키고, 일정 시간이 경과하면 coral2의 상태를 변경
    coral2_spawn_timer--;
    if (coral2_spawn_timer <= 0) {
        coral2_visible = !coral2_visible; // coral2의 상태를 변경하여 나타나거나 사라지도록 설정
        coral2_spawn_timer = CORAL2_SPAWN_TIME; // 타이머 재설정
    }
    // coral3_spawn_timer를 감소시키고, 일정 시간이 경과하면 coral2의 상태를 변경=>추가
    coral3_spawn_timer--;
    if (coral3_spawn_timer <= 0) {
        coral3_visible = !coral3_visible; // coral2의 상태를 변경하여 나타나거나 사라지도록 설정
        coral3_spawn_timer = CORAL3_SPAWN_TIME; // 타이머 재설정
    }

    if (!stop) {
        int x = turtle->getX();
        int y = turtle->getY();

        if (f_list[0]) {
            x -= 1;
            f_list[0] = false;
        }
        else if (f_list[1]) {
            x += 1;
            f_list[1] = false;
        }
        else if (f_list[2]) {
            y -= 1;
            f_list[2] = false;
        }
        else if (f_list[3]) {
            y += 1;
            f_list[3] = false;
        }

        if (x >= SCREEN_WIDTH_STAGE2) x = SCREEN_WIDTH_STAGE2 - 1;
        if (x < 0) x = 0;
        if (y >= SCREEN_HEIGHT_STAGE2) y = SCREEN_HEIGHT_STAGE2 - 1;
        if (y < 0) y = 0;

        // 거북이가 산호에 닿지 않는 경우에만 이동
        if (x >= 0 && x < SCREEN_WIDTH_STAGE2 && y >= 0 && y < SCREEN_HEIGHT_STAGE2 && !Maze::isCoral(x, y)) {
            turtle->move(x, y); // 이동 가능한 경우에만 이동 메서드 호출
        }
    }
    // 거북이의 무적 상태 업데이트
    if (turtle->isInvincible()) {
        // 무적 시간 감소
        turtle->setInvincibleTimer(turtle->getInvincibleTimer() - 1);
        // 무적 시간이 끝나면 무적 상태 해제
        if (turtle->getInvincibleTimer() <= 0) {
            turtle->setInvincible(false);
        }
    }



    // 모든 산호와의 충돌 확인
    for (int i = 0; i < SCREEN_HEIGHT_STAGE2; i++) {
        for (int j = 0; j < SCREEN_WIDTH_STAGE2; j++) {
            if (Maze::maze[i][j] == 2 && turtle->getX() == j && turtle->getY() == i && coral2_visible) {
                Mix_PlayChannel(-1, coral_sound, 0);
                turtle->GetAttackted(1); // 거북이가 산호와 충돌할 때 체력 감소
            }
            else if (Maze::maze[i][j] == 3 && turtle->getX() == j && turtle->getY() == i && coral3_visible) {
                //음향
                Mix_PlayChannel(-1, coral_sound, 0);
                turtle->GetAttackted(1); // 거북이가 산호와 충돌할 때 체력 감소
            }
        }
    }

    //소라게와 충돌확인 
    if (turtle->isCollision_Conch(conch1) || turtle->isCollision_Conch(conch2) || turtle->isCollision_Conch(conch3) || turtle->isCollision_Conch(conch4)) {
        Mix_PlayChannel(-1, conch_sound, 0);
        turtle->GetAttackted(1);
    }


    // 토끼와의 충돌 확인
    if (turtle->isCollision_Rabbit(rabbit)) {
        Mix_PlayChannel(-1, rabbit_sound, 0); // 토끼와 부딪힐 때 효과음 출력
        rabbit->setCount(rabbit->getCount() + 1);
        rabbit->spawn();
    }

    //종료조건
    if (rabbit->getCount() == 5) {
        game_result = 1; //승리
        g_current_game_phase = PHASE_STAGE2_ENDING;
        viewedEndings[1][1] = true;
        SDL_Delay(1000);
    }
    if (turtle->getHealth() <= 0) {
        game_result = 2; //실패
        g_current_game_phase = PHASE_STAGE2_ENDING;
        viewedEndings[1][0] = true;
        SDL_Delay(1000);
    }


}

void Stage2::Render() {

    //배경배경 그리기
    SDL_RenderCopy(g_renderer, stage2_bgbgbg_texture, NULL, &stage2_bgbgbg_destination_rect);

    //배경 그리기
    SDL_RenderCopy(g_renderer, stage2_bg_texture, &stage2_bg_source_rect, &stage2_bg_destination_rect);


    COORD cur;
    cur.X = 0;
    cur.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    for (int i = 0; i < SCREEN_HEIGHT_STAGE2; i++) {
        for (int j = 0; j < SCREEN_WIDTH_STAGE2; j++) {
            if (Maze::maze[i][j] == 0) {
                cout << " ";
            }
            else if (Maze::maze[i][j] == 1) {
                coral_destination_rect.x = j * GRID_stage2 + TILE_SIZE + 6;
                coral_destination_rect.y = i * GRID_stage2 + TILE_SIZE;
                SDL_RenderCopy(g_renderer, coral_texture, NULL, &coral_destination_rect);
                cout << " ";
            }
            else if (Maze::maze[i][j] == 2) {
                // coral2 렌더링
                if (coral2_visible) {
                    coral2_destination_rect.x = j * GRID_stage2 + TILE_SIZE + 6;
                    coral2_destination_rect.y = i * GRID_stage2 + TILE_SIZE;
                    SDL_RenderCopy(g_renderer, coral2_texture, NULL, &coral2_destination_rect);

                }

            }
            else if (Maze::maze[i][j] == 3) {
                // coral2 렌더링
                if (coral3_visible) {
                    coral2_destination_rect.x = j * GRID_stage2 + TILE_SIZE + 6;
                    coral2_destination_rect.y = i * GRID_stage2 + TILE_SIZE;
                    SDL_RenderCopy(g_renderer, coral2_texture, NULL, &coral2_destination_rect);

                }
            }
        }
        cout << endl;
    }


    //토끼개수 간 그리기
    for (int i = 0; i < rabbit->getCount(); i++) {
        gan_destination_rect.x = GRID_stage2 * 5 + i * GRID_stage2 + TILE_SIZE + 6;
        gan_destination_rect.y = TILE_SIZE + SCREEN_HEIGHT_STAGE2 * GRID_stage2 + 5;
        SDL_RenderCopy(g_renderer, gan_texture, NULL, &gan_destination_rect);
    }




    //캐릭터그리기
    // 토끼
    if (rabbit->getX() != turtle->getX() || rabbit->getY() != turtle->getY()) {
        rabbit_destination_rect.x = rabbit->getX() * GRID_stage2 + TILE_SIZE + 6;
        rabbit_destination_rect.y = rabbit->getY() * GRID_stage2 + TILE_SIZE;
        SDL_RenderCopy(g_renderer, rabbit_texture, NULL, &rabbit_destination_rect);
    }

    //거북이 그리기

    if (!turtle->isInvincible()) {
        // 무적 상태가 아니거나, 무적 상태이지만 0.5초마다 깜박거리도록 함
        turtle_destination_rect.x = turtle->getX() * GRID_stage2 + TILE_SIZE + 6;
        turtle_destination_rect.y = turtle->getY() * GRID_stage2 + TILE_SIZE;
        SDL_RenderCopy(g_renderer, turtle_texture, NULL, &turtle_destination_rect);
    }
    else if ((turtle->isInvincible() && (SDL_GetTicks() / 50) % 2 == 0)) {
        turtle_destination_rect.x = turtle->getX() * GRID_stage2 + TILE_SIZE + 6;
        turtle_destination_rect.y = turtle->getY() * GRID_stage2 + TILE_SIZE;
        SDL_RenderCopy(g_renderer, turtle2_texture, NULL, &turtle_destination_rect);
    }

    //거북이 체력 그리기 
    for (int i = 0; i < 3; i++) {
        heart0_destination_rect.x = i * GRID_stage2 + TILE_SIZE + 6;
        heart0_destination_rect.y = TILE_SIZE + SCREEN_HEIGHT_STAGE2 * GRID_stage2 + 5;
        SDL_RenderCopy(g_renderer, heart0_texture, NULL, &heart0_destination_rect);
    }
    for (int i = 0; i < turtle->getHealth(); i++) {
        heart2_destination_rect.x = i * GRID_stage2 + TILE_SIZE + 6;
        heart2_destination_rect.y = TILE_SIZE + SCREEN_HEIGHT_STAGE2 * GRID_stage2 + 5;
        SDL_RenderCopy(g_renderer, heart2_texture, NULL, &heart2_destination_rect);
    }



    //소라게1 그리기
    conch_destination_rect.x = conch1->getX() * GRID_stage2 + TILE_SIZE + 6;
    conch_destination_rect.y = conch1->getY() * GRID_stage2 + TILE_SIZE;
    SDL_RenderCopy(g_renderer, conch_texture, NULL, &conch_destination_rect);
    //소라게2 그리기
    conch_destination_rect.x = conch2->getX() * GRID_stage2 + TILE_SIZE + 6;
    conch_destination_rect.y = conch2->getY() * GRID_stage2 + TILE_SIZE;
    SDL_RenderCopy(g_renderer, conch_texture, NULL, &conch_destination_rect);
    //소라게3 그리기
    conch_destination_rect.x = conch3->getX() * GRID_stage2 + TILE_SIZE + 6;
    conch_destination_rect.y = conch3->getY() * GRID_stage2 + TILE_SIZE;
    SDL_RenderCopy(g_renderer, conch_texture, NULL, &conch_destination_rect);
    //소라게4 그리기
    conch_destination_rect.x = conch4->getX() * GRID_stage2 + TILE_SIZE + 6;
    conch_destination_rect.y = conch4->getY() * GRID_stage2 + TILE_SIZE;
    SDL_RenderCopy(g_renderer, conch_texture, NULL, &conch_destination_rect);

    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);


    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);

    if (stage2_status != 1) {//일시정지 상태 혹은 대기 상태
        SDL_RenderCopy(g_renderer, wait_texture, NULL, &wait_destination_rect);
        switch (stage2_status)
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
void Stage2::Reset() {//재시작시 상태
    //객체 초기화
    delete turtle;
    delete rabbit;
    delete coral;
    delete coral2;
    delete conch1;
    delete conch2;
    delete conch3;
    delete conch4;

    turtle = new Turtle(1, 1, 0, 3, 0);
    rabbit = new Rabbit(18, 17, 1, 3);
    coral = new Coral(0, 0, 0, 0, 1);
    coral2 = new Coral2(0, 0, 0, 0, 1);
    conch1 = new Conch(15, 15, 0, 0, 1, 0, 0);
    conch2 = new Conch(10, 10, 0, 0, 1, 0, 0);
    conch3 = new Conch(20, 3, 0, 0, 1, 0, 0);
    conch4 = new Conch(25, 25, 0, 0, 1, 0, 0);

    //기타
    stop = true; //정지 상황으로 초기화

    flip = SDL_FLIP_HORIZONTAL;

    alpha = 0;
    stage2_status = 0;

    //음향 끄기
    Mix_HaltChannel(-1);//모든 사운드 중지

    //음악 다시 시작
    Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작


    //일시정지 시간 초기화
    totalPauseTime = 0;
    stage2_startTime = 0;
    pauseStartTime = 0;
    totalPauseTime_2 = 0;


}


Stage2::~Stage2() {

    SDL_DestroyTexture(stage2_bg_texture);
    SDL_DestroyTexture(stage2_bgbgbg_texture);
    SDL_DestroyTexture(turtle_texture);
    SDL_DestroyTexture(rabbit_texture);
    SDL_DestroyTexture(coral_texture);
    SDL_DestroyTexture(coral2_texture);
    SDL_DestroyTexture(gan_texture);
    SDL_DestroyTexture(heart0_texture);
    SDL_DestroyTexture(heart2_texture);
    SDL_DestroyTexture(conch_texture);
    SDL_DestroyTexture(wait_texture);
    SDL_DestroyTexture(button_continue);
    SDL_DestroyTexture(button_main);
    SDL_DestroyTexture(ready_texture);


    delete turtle;
    delete rabbit;
    delete coral;
    delete coral2;
    delete conch1;
    delete conch2;


    Mix_FreeMusic(background_music);
    Mix_FreeChunk(button_sound);
    Mix_FreeChunk(rabbit_sound);
    Mix_FreeChunk(coral_sound);
    Mix_FreeChunk(conch_sound);



}