#pragma once

#include "STAGE.h"


class Phase_stage1Intro : public PhaseInterface {
private:
    // 배경 텍스쳐
    SDL_Texture* bg_texture;
    SDL_Rect bg_destination;

    SDL_Texture* first_intro_texture;
    SDL_Texture* second_intro_texture;
    SDL_Texture* third_intro_texture;
    SDL_Texture* fourth_intro_texture;
    SDL_Texture* fifth_intro_texture;
    Mix_Music* intro_music;
    // SDL_Rect intro_destination;

    int count;

public:
    Phase_stage1Intro();
    ~Phase_stage1Intro();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};