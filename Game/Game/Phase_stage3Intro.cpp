#include "Phase_stage3Intro.h"


Phase_stage3Intro::Phase_stage3Intro() {
    // 배경 텍스쳐
    SDL_Surface* temp_sheet_surface;

    bg_destination.x = 40;
    bg_destination.y = 40;
    bg_destination.w = screenWidth - 80;
    bg_destination.h = screenHeight - 80;


    background_music = Mix_LoadMUS("../../Resources/stage3/Intro.mp3");
    Mix_VolumeMusic(128);

    temp_sheet_surface = IMG_Load("../../Resources/stage3/intro1.png");
    first_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/intro2.png");
    second_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/intro3.png");
    third_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/intro4.png");
    fourth_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/stage3/intro5.png");
    fifth_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    bg_texture = first_intro_texture;
    count = 0; //0,1,2 배경 이미지 출력할 것

}

void Phase_stage3Intro::HandleEvents() {
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

void Phase_stage3Intro::Update() {
    if (count == 5) //n개 다 봤으면 스테이지로 전환
        g_current_game_phase = PHASE_STAGE3_GAME;
}

void Phase_stage3Intro::Render() {

    if (count == 0) {
        bg_texture = first_intro_texture;
    }
    else if (count == 1) {
        bg_texture = second_intro_texture;
    }
    else if (count == 2) {
        bg_texture = third_intro_texture;
    }
    else if (count == 3) {
        bg_texture = fourth_intro_texture;
    }
    else if (count == 4) {
        bg_texture = fifth_intro_texture;
    }

    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination);
    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);
    SDL_RenderPresent(g_renderer);
}

void Phase_stage3Intro::Reset() {
    count = 0;
    bg_texture = first_intro_texture;
    Mix_PlayMusic(background_music, -1);
    //game_result = 0;
}

Phase_stage3Intro::~Phase_stage3Intro() {
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(first_intro_texture);
    SDL_DestroyTexture(second_intro_texture);
    SDL_DestroyTexture(third_intro_texture);
    SDL_DestroyTexture(fourth_intro_texture);

    SDL_DestroyTexture(fame_texture);
    Mix_FreeMusic(background_music);


}