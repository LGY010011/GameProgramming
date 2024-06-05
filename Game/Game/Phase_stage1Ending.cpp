#include "Phase_stage1Ending.h"

Phase_stage1Ending::Phase_stage1Ending() {
    //민들레의 HP가 0이 된 엔딩이미지1
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending1.png");
    stg1_dandelion_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    // 엔딩이미지1의 게임오버이미지
    SDL_Surface* temp_sheet_surface2 = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending1_1.png");
    stg1_dandelion_ending_texture2 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface2);
    SDL_FreeSurface(temp_sheet_surface2);//해제 필수

    //강아지똥의 HP가 0이 된 엔딩이미지1
    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending2.png");
    stg1_dogPoop_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    // 엔딩이미지2의 게임오버이미지
    SDL_Surface* temp_sheet_surface3 = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending2_1.png");
    stg1_dogPoop_ending_texture2 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface3);
    SDL_FreeSurface(temp_sheet_surface3);//해제 필수

    //해피엔딩 이미지
    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending3.png");
    stg1_happy_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    stg1_ending_destination.x = 40;
    stg1_ending_destination.y = 40;
    stg1_ending_destination.w = screenWidth - 80;
    stg1_ending_destination.h = screenHeight - 80;


    //새드엔딩 효과음 로드
    stg1_gosad_sound = Mix_LoadWAV("../../Resources/stage1/sounds/sadEnding.wav");
    //해피엔딩 효과음 로드
    stg1_gohappy_sound = Mix_LoadWAV("../../Resources/stage1/sounds/happyEnding.wav");

    //버튼 텍스쳐
    SDL_Surface* tmp_surface1 = IMG_Load("../../Resources/stage1/general/btn_retry.png");
    stg1_retry_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
    SDL_FreeSurface(tmp_surface1);

    stg1_retry_button_destination.x = 800;
    stg1_retry_button_destination.y = 580;
    stg1_retry_button_destination.w = 100;
    stg1_retry_button_destination.h = 100;

    SDL_Surface* tmp_surface2 = IMG_Load("../../Resources/stage1/general/btn_main.png");
    stg1_home_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
    SDL_FreeSurface(tmp_surface2);

    stg1_home_button_destination.x = stg1_retry_button_destination.x + 110;
    stg1_home_button_destination.y = stg1_retry_button_destination.y;
    stg1_home_button_destination.w = 100;
    stg1_home_button_destination.h = 100;


    stg1_button = false;
    stg1_endingPhaseStartTime = 0;
    stg1_buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
    stg1_pageCheck = 0;

    game_result = 0;
}

void Phase_stage1Ending::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                if (stg1_button) {//버튼이 켜져있으면 버튼을 누르는 순간

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;
                    //retry
                    if (mouse_x >= stg1_retry_button_destination.x && mouse_x <= stg1_retry_button_destination.x + stg1_retry_button_destination.w &&
                        mouse_y >= stg1_retry_button_destination.y && mouse_y <= stg1_retry_button_destination.y + stg1_retry_button_destination.h
                        )
                        stg1_buttonPushed = 1;
                    //main
                    else if (mouse_x >= stg1_home_button_destination.x && mouse_x <= stg1_home_button_destination.x + stg1_home_button_destination.w &&
                        mouse_y >= stg1_home_button_destination.y && mouse_y <= stg1_home_button_destination.y + stg1_home_button_destination.h
                        )
                        stg1_buttonPushed = 2;
                }

            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN) {
                stg1_pageCheck++;
            }

            break;
        }
    }
}

void Phase_stage1Ending::Update() {
    if (g_prev_game_phase != g_current_game_phase)
        stg1_endingPhaseStartTime = SDL_GetTicks();

    int currentTime = SDL_GetTicks();
    if (currentTime - stg1_endingPhaseStartTime > 3000) { // 3초가 지났다면
        // 버튼 보이게 함
        stg1_button = true;
    }
    else
        stg1_button = false;
    /*
    if (stg1_pageCheck == 1) {
        g_current_game_phase = PHASE_INTRO;
        game_result = 0;
    }*/

    //retry 버튼 누르면 스테이지
    if (stg1_buttonPushed == 1) {
        g_current_game_phase = PHASE_STAGE1_GAME;
    } //main 버튼 누르면 인트로
    else if (stg1_buttonPushed == 2) {
        g_current_game_phase = PHASE_INTRO;
    }
}


void Phase_stage1Ending::Render() {
    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);

    SDL_Texture* stg1_ending_texturetemp = NULL;
    if (game_result == 1) {
        stg1_ending_texturetemp = stg1_dandelion_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_dandelion_ending_texture1, NULL, &stg1_ending_destination);
        if (stg1_button) stg1_ending_texturetemp = stg1_dandelion_ending_texture2;
    }
    else if (game_result == 2) {
        stg1_ending_texturetemp = stg1_dogPoop_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_dogPoop_ending_texture1, NULL, &stg1_ending_destination);
        if (stg1_button) stg1_ending_texturetemp = stg1_dogPoop_ending_texture2;
    }
    else if (game_result == 3) {
        stg1_ending_texturetemp = stg1_happy_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_happy_ending_texture1, NULL, &stg1_ending_destination);
    }
    SDL_RenderCopy(g_renderer, stg1_ending_texturetemp, NULL, &stg1_ending_destination);

    if (stg1_button) {
        SDL_RenderCopy(g_renderer, stg1_retry_button_texture, NULL, &stg1_retry_button_destination);
        SDL_RenderCopy(g_renderer, stg1_home_button_texture, NULL, &stg1_home_button_destination);
    }

    SDL_RenderPresent(g_renderer);
}

void Phase_stage1Ending::Reset() {
    //페이즈 바뀌고 3초세기
    stg1_endingPhaseStartTime = SDL_GetTicks();
    //배경음 중지
    Mix_HaltMusic();
    stg1_button = false;
    stg1_buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
    stg1_pageCheck = 0;
    //엔딩 효과음 재생
    if (game_result == 1 || game_result == 2) {
        Mix_PlayChannel(-1, stg1_gosad_sound, 0);
    }
    else if (game_result == 3) {
        Mix_PlayChannel(-1, stg1_gohappy_sound, 0);
    }
    ///endingPhaseStartTime = 0;
}

Phase_stage1Ending::~Phase_stage1Ending() {

    SDL_DestroyTexture(stg1_retry_button_texture);
    SDL_DestroyTexture(stg1_home_button_texture);
    SDL_DestroyTexture(stg1_dandelion_ending_texture1);
    SDL_DestroyTexture(stg1_dogPoop_ending_texture1);
    SDL_DestroyTexture(stg1_happy_ending_texture1);
    SDL_DestroyTexture(stg1_dandelion_ending_texture2);
    SDL_DestroyTexture(stg1_dogPoop_ending_texture2);

    Mix_FreeChunk(stg1_gosad_sound);
    Mix_FreeChunk(stg1_gohappy_sound);

}
