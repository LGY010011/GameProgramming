#include "Phase_Stage1Intro.h"

Phase_stage1Intro::Phase_stage1Intro() {
    // 배경 텍스쳐
    SDL_Surface* temp_sheet_surface;

    bg_destination.x = 40;
    bg_destination.y = 40;
    bg_destination.w = screenWidth - 80;
    bg_destination.h = screenHeight - 80;

    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg1_intro1.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load stg1_intro1.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    first_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg1_intro2.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load stg1_intro2.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    second_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg1_intro3.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load stg1_intro3.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    third_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg1_intro4.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load stg1_intro4.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    fourth_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg1_intro5.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load stg1_intro5.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    fifth_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);

    // 프레임 로드
    temp_sheet_surface = IMG_Load("../../Resources/stage1/general/photoframe.png");
    if (temp_sheet_surface == nullptr) {
        std::cout << "Failed to load photoframe.png: " << IMG_GetError() << std::endl;
        // Handle error
    }
    fame_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    // 인트로 배경음 로드
    intro_music = Mix_LoadMUS("../../Resources/stage1/sounds/introCartoonbgm.mp3");
    if (intro_music == NULL) {
        std::cout << "intro_music load fail: " << Mix_GetError() << std::endl;
    }

    frame_destination.x = 0;
    frame_destination.y = 0;
    frame_destination.w = screenWidth;
    frame_destination.h = screenHeight;

    bg_texture = first_intro_texture;
    count = 0; // 0,1,2 배경 이미지 출력할 것
}

void Phase_stage1Intro::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_flag_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN)
                count++;
            break;
        }
    }
}

void Phase_stage1Intro::Update() {
    if (count == 5) { // 4개 다 봤으면 스테이지로 전환
        g_current_game_phase = PHASE_STAGE1_GAME;
    }
}

void Phase_stage1Intro::Render() {
    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);
    switch (count) {
    case 0:
        bg_texture = first_intro_texture;
        break;
    case 1:
        bg_texture = second_intro_texture;
        break;
    case 2:
        bg_texture = third_intro_texture;
        break;
    case 3:
        bg_texture = fourth_intro_texture;
        break;
    case 4:
        bg_texture = fifth_intro_texture;
        break;
    }
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination);
    SDL_RenderPresent(g_renderer);
}

void Phase_stage1Intro::Reset() {
    if (g_current_game_phase == PHASE_STAGE1_INTRO) {
        Mix_PlayMusic(intro_music, -1);
    }
    else {
        Mix_HaltMusic();
    }
    count = 0;
    bg_texture = first_intro_texture;
}

Phase_stage1Intro::~Phase_stage1Intro() {
    SDL_DestroyTexture(first_intro_texture);
    SDL_DestroyTexture(second_intro_texture);
    SDL_DestroyTexture(third_intro_texture);
    SDL_DestroyTexture(fourth_intro_texture);
    SDL_DestroyTexture(fifth_intro_texture);
    SDL_DestroyTexture(fame_texture);

    if (intro_music != nullptr) {
        Mix_FreeMusic(intro_music);
        intro_music = nullptr;
    }
}